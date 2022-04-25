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

    for(int i = 0 ; i< data.numberOfScans ; i++)
    {
        if(!(data.Data[i].scanDistance < 0.15)) // Polomer robota
        {
            //OFFSET -> Robot nezacina v 0,0.
            x = robot.getPosX() + data.Data[i].scanDistance*0.001 * cos(robot.getRotation() - data.Data[i].scanAngle*(M_PI/180))+OFFSET;
            y = robot.getPosY() + data.Data[i].scanDistance*0.001 * sin(robot.getRotation() - data.Data[i].scanAngle*(M_PI/180))+OFFSET;

            x_index = floor(x/0.05); //5x5cm stvorec v mape
            y_index = floor(y/0.05); //

            map[x_index][y_index] = 1 ;
        }
    }

}
void Mapper::generateMap()
{
    wfile.open("room1");
    if(wfile.is_open())
        for(int j = 0; j<VERTICAL_MAP_LIMIT;j++)
        {
            wfile<< '\n';
            for(int i = 0; i<HORIZONTAL_MAP_LIMIT;i++)
            {
               wfile <<map[i][j] ;
            }
        }
    wfile.close();
}

void Mapper::loadMap()
{
    rfile.open("model");

    if(rfile.is_open())
    {
        for(int i = 0 ; i > HORIZONTAL_MAP_LIMIT ; i++)
        {
            for(int j = 0 ; j > VERTICAL_MAP_LIMIT ; j++)
            {
                rfile >> map[i][j];
            }
        }
    }
    rfile.close();
}

void Mapper::FloodFill()
{//https://helloacm.com/flood-fill-algorithm-using-breadth-first-search/
        unordered_set<string> vis;
        queue<vector<int>> Q;
        Q.push({xC, yC, 8});
        vector<int> d{1, 0, -1, 0, 1};
        auto cur = map[xC][yC];
        while (!Q.empty()) {
            auto p = Q.front();
            Q.pop();
            auto key = std::to_string(p[0]) + "," + std::to_string(p[1]);
            if (vis.count(key)) continue;
            vis.insert(key);
            map[p[0]][p[1]] = 8;
            for (int i = 0; i < 4; ++ i) {
                int nx = p[0] + d[i];
                int ny = p[1] + d[i + 1];
                if ((nx >= 0) && (ny >= 0) && (nx < HORIZONTAL_MAP_LIMIT) && (ny < VERTICAL_MAP_LIMIT) && (map[nx][ny] == cur)) {
                    Q.push({nx, ny});
                }
            }
        }
}
