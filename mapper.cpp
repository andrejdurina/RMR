
#include "mapper.h"

Mapper::Mapper()
{
    for(int i = 0; i<HORIZONTAL_MAP_LIMIT;i++)
        for(int j = 0; j<VERTICAL_MAP_LIMIT;j++)
        {
            map[i][j] = 0;
        }
}

void Mapper::processData(Position &robot, LaserMeasurement data)
{
    Coords coords;
    Coords_I coords_i;
    for(int i = 0 ; i< data.numberOfScans ; i++)
    {
        if(!(data.Data[i].scanDistance < 0.15)) // Polomer robota
        {

            coords.x = robot.getPosX() + data.Data[i].scanDistance*0.001 * cos(robot.getRotation() - data.Data[i].scanAngle*(M_PI/180));
            coords.y = robot.getPosY() + data.Data[i].scanDistance*0.001 * sin(robot.getRotation() - data.Data[i].scanAngle*(M_PI/180));

            coords_i = fromWorldToIndex(coords);
            map[coords_i.x][coords_i.y] = 1 ;
        }
    }
}
void Mapper::saveMap()
{
    wfile.open("room_saved.txt");
    if(wfile.is_open())
    {
        for(int j = 0; j<VERTICAL_MAP_LIMIT;j++)
        {
            wfile << '\n';
            for(int i = 0; i<HORIZONTAL_MAP_LIMIT;i++)
            {
               wfile << map[i][j] ;
            }
        }
    }
    wfile.close();
}

void Mapper::loadMap()
{   int tmp;
    rfile.open("room_scaned");

    if(rfile.is_open())
    {
        for(int j = 0; j<VERTICAL_MAP_LIMIT;j++)
        {
            for(int i = 0; i<HORIZONTAL_MAP_LIMIT;i++)
            {
                tmp = rfile.get();
                if(tmp != '\n')
                   map[i][j] = tmp-'0';
                else
                    i = i - 1;
            }
        }
    }
    rfile.close();
}

void Mapper::saveFloodedMap()
{
    char buffer [6];
    wfile.open("FloorFiller.txt");
    if(wfile.is_open())
    {
        for(int j = 0; j<VERTICAL_MAP_LIMIT;j++)
        {
            wfile<< '\n';
            for(int i = 0; i<HORIZONTAL_MAP_LIMIT;i++)
            {
               snprintf ( buffer, 6, "%4d ", cpy_map[i][j] );
               wfile << buffer;
            }
        }
    }
    wfile.close();
}

void Mapper::postProcessData()
{
    memcpy(cpy_map,map,sizeof (int)*HORIZONTAL_MAP_LIMIT*VERTICAL_MAP_LIMIT);
    for(int i = 5 ; i < (HORIZONTAL_MAP_LIMIT-5) ; i++)
    {
        for(int j = 5 ; j < (VERTICAL_MAP_LIMIT-5) ; j++)
        {
           for(int k = -5 ; k <= 5 ; k++)//Robot ma 22cm polomer, preto 5 policok bo 5x5 = 25cm
           {
                for(int q = -5 ; q <= 5 ; q++) // Nechceme plusko , ale stvorcek robi to potom ciary po stenach.
                {
                     if(map[i+k][j+q] == 1)
                     {
                         cpy_map[i][j] = 1;
                         break;
                     }
                }
           }
        }
    }
}

void Mapper::FloodFill(Coords coords, Position &robot)
{
        finish = coords;
        vector<int> point;
        queue<vector<int>> Queue;
        vector<int> neighbour_x = {-1,0,1,0};
        vector<int> neighbour_y = {0,-1,0,1};
        int x,y;

        Coords_I converted_coords = fromWorldToIndex(coords);
        postProcessData();
        //FloodFill
        Queue.push({converted_coords.x,converted_coords.y, 2}); //Cielovy bod robota
        if(cpy_map[converted_coords.x][converted_coords.y] == 0) // Kontrola ci je dosiahnutelny cielovy bod.
            cpy_map[converted_coords.x][converted_coords.y] = 2;
        else return;

        Coords_I robot_pos;
        robot_pos = fromWorldToIndex(robot.getPosition());

        while ((cpy_map[robot_pos.x][robot_pos.y] == 0) && !Queue.empty()){ // Ohodnoti to po polohu robota alebo pokial queue neni empty.
           point =  Queue.front();
           for(int i = 0 ; i < 4 ; i++) // Kontrola susedov.
           {      x = point[0]+neighbour_x[i];
                  y = point[1]+neighbour_y[i];
               if(!(x >= HORIZONTAL_MAP_LIMIT || y >= VERTICAL_MAP_LIMIT || x < 0 || y < 0)) // Limity mapy +/-
                   if(cpy_map[x][y] == 0 ){                                                   // V kopii mapy[x,y] nieje prekazka/ine cislo.
                        Queue.push({x,y,point[2]+1}) ;
                        cpy_map[x][y] = point[2]+1;
                   }
           }
           Queue.pop();
        }
}

Coords_I Mapper::fromWorldToIndex(Coords coords)
{
    //5x5 stvorec v mape (cm)
    //OFFSET -> Robot nezacina v 0,0.
    return Coords_I(floor((coords.x+OFFSET)/0.05),floor((coords.y+OFFSET)/0.05));
}

Coords Mapper::fromIndexToWorld(Coords_I coords)
{
    return Coords((coords.x*0.05)-OFFSET,(coords.y*0.05)-OFFSET);
}
deque<Coords> Mapper::generateWaypoints(Position &robot){

    waypoints.clear();
    int max,robot_x,robot_y;
    int actual_direction = 1,next_direction = 0;

    vector<int> direction_X = {0,1,0,-1};
    vector<int> direction_Y = {1,0,-1,0};

        robot_x = fromWorldToIndex(robot.getPosition()).x;
        robot_y = fromWorldToIndex(robot.getPosition()).y;

        max = cpy_map[robot_x][robot_y];
     while(max != 2)                                                     // Pokial nedosiahne zelany bod robota.
    {
        for(int i = 0 ; i < 4; i++ )
        {   int dir = actual_direction + i;                              // Kontrola mapy v aktualnom smere.
            if(dir > 3)                                                  // Ked to nebude ani vlavo tak sa skontroluje zase v clockwise smere.
                dir = dir - 4;
            if(cpy_map[robot_x+direction_X[dir]][robot_y+direction_Y[dir]] == (max-1))
            {
                next_direction = dir;                                      // Smer robota hore,vpravo,dole,vlavo.
                max = cpy_map[robot_x+direction_X[dir]][robot_y+direction_Y[dir]];

                if(actual_direction != next_direction)
                {
                     waypoints.push_back(fromIndexToWorld(Coords_I(robot_x,robot_y)));
                     actual_direction = next_direction;
                }

                robot_x = robot_x+direction_X[dir];
                robot_y = robot_y+direction_Y[dir];
                break;
            }
        }
    }
     waypoints.push_back(finish);
     return waypoints;
}
