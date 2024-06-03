#include<c++/4.8.3//vector>
#include<c++/4.8.3//queue>
#include<c++/4.8.3//string>
#include<c++/4.8.3//unordered_map>
using namespace std;

vector<vector<int>> mat(16, vector<int>(16, 0));
vector<vector<string>> walls;

  int m = 8;
  int n = 8;

  int x=0;
  int y=0;
// Ultrasonic pins
int trigPin1 = PA8;    // TRIG pin for Ultrasonic1
int echoPin1 = PB8;    // ECHO pin for Ultrasonic1
int trigPin2 = PB1;    // TRIG pin for Ultrasonic2
int echoPin2 = PA0;    //ECHO pin for Ultrasonic2
vector<vector<int>>maze;
char orientation_marker = 'N';

// IR sensor pins 
int ir1 = PB11; // input pin for front-left IRsensor 
int ir2 = PB10; // input pin for front-right IRsensor
int ir3 = PA5; // input pin for left IRsensor
int ir4 = PA4; // input pin for right IRsensor
float duration1, distance1_cm;
float duration2, distance2_cm;

int straight_time = 670;
int left_delay  = 700;
int right_delay = 700;
int uturn_delay = 1400;
// Motor_1 Connection
#define ENABLE_1 PA9
#define MOTOR1_A PB15
#define MOTOR1_B PB14

// Motor_2 Connection
#define ENABLE_2 PB6
#define MOTOR2_A PB3
#define MOTOR2_B PA15

int value1,value2,value3, value4;

// function for rotation of motors taking speeds as parameters
void direction(int en1,int en2){
  analogWrite(ENABLE_1, en1);
  analogWrite(ENABLE_2, en2);
  digitalWrite(MOTOR1_A , HIGH);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , HIGH);
  digitalWrite(MOTOR2_B , LOW);
}

void left_turn(){
  int prev_time = 0; 
  analogWrite(ENABLE_1, 150);
  analogWrite(ENABLE_2, 250);
  digitalWrite(MOTOR1_A , HIGH);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , LOW);
  digitalWrite(MOTOR2_B , HIGH);
  int current_time=millis();
  if(current_time - prev_time == left_delay){
    digitalWrite(MOTOR1_A , LOW);
    digitalWrite(MOTOR1_B , LOW);
    digitalWrite(MOTOR2_A , LOW);
    digitalWrite(MOTOR2_B , LOW);
    delay(800);
  }
  prev_time = current_time;
}

void right_turn(){
  int prev_time=0;
  analogWrite(ENABLE_1, 250);
  analogWrite(ENABLE_2, 190);
  digitalWrite(MOTOR1_A , LOW);
  digitalWrite(MOTOR1_B , HIGH);
  digitalWrite(MOTOR2_A , HIGH);
  digitalWrite(MOTOR2_B , LOW);
  int current_time=millis();
  if(current_time -prev_time == right_delay){
    digitalWrite(MOTOR1_A , LOW);
    digitalWrite(MOTOR1_B , LOW);
    digitalWrite(MOTOR2_A , LOW);
    digitalWrite(MOTOR2_B , LOW);
    delay(800);
  }
  prev_time=current_time;
}

void straight(){
  int prev_time = 0;
  analogWrite(ENABLE_1, 200);
  analogWrite(ENABLE_2, 200);
  digitalWrite(MOTOR1_A , HIGH);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , HIGH);
  digitalWrite(MOTOR2_B , LOW);
  if(distance1_cm < distance2_cm){  
    direction(210,190);// speed change
  }
  else if(distance1_cm > distance2_cm){
    direction(190,210);// speed change 
  }
  int current_time1 = millis();
  if(current_time1 - prev_time == straight_time){
    digitalWrite(MOTOR1_A , LOW);
    digitalWrite(MOTOR1_B , LOW);
    digitalWrite(MOTOR2_A , LOW);
    digitalWrite(MOTOR2_B , LOW);
    int value1 = digitalRead(ir1);
    int value2 = digitalRead(ir2);
    int value3 = digitalRead(ir3);
    int value4 = digitalRead(ir4);
    delay(100);
  }
  prev_time= current_time1;
}

void u_turn(){
  int prev_time = 0;
  analogWrite(ENABLE_1, 200);
  analogWrite(ENABLE_2, 200);
  digitalWrite(MOTOR1_A , HIGH);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , LOW);
  digitalWrite(MOTOR2_B , HIGH);
  int current_time=millis();
  if(current_time-prev_time == uturn_delay){
    digitalWrite(MOTOR1_A , LOW);
    digitalWrite(MOTOR1_B , LOW);
    digitalWrite(MOTOR2_A , LOW);
    digitalWrite(MOTOR2_B , LOW);
    delay(800);
  }
  prev_time = current_time;
}

string mapping_sensor_2(vector<int> &sen)
{

  string s = "";
  for (int x = 0; x < 4; x++)
  {
    s.push_back(String(sen[x])[0]);
  }
  return s;
}
unordered_map<string, string> mapping_sensor(vector<int> &sensors)
{
  // left ,front and right//
  unordered_map<string, string> sensor_mapping;

  // 1 st case bot facing NORTH //
  if (orientation_marker == 'N')
  {
    sensor_mapping["0000"] = "NULL";
    sensor_mapping["0110"] = "N";
    sensor_mapping["0001"] = "E";
    sensor_mapping["1000"] = "W";
    sensor_mapping["0111"] = "NE";
    sensor_mapping["1110"] = "NW";
    sensor_mapping["1001"] = "EW";
    sensor_mapping["1111"] = "NEW";
  }
  // 1 st case bot facing EAST //
  else if (orientation_marker == 'E')
  {
    sensor_mapping["0000"] = "NULL";
    sensor_mapping["0110"] = "E";
    sensor_mapping["0001"] = "S";
    sensor_mapping["1000"] = "N";
    sensor_mapping["0111"] = "ES";
    sensor_mapping["1110"] = "NE";
    sensor_mapping["1001"] = "NS";
    sensor_mapping["1111"] = "ENS";
  }
  // 1 st case bot facing WEST //
  else if (orientation_marker == 'W')
  {
    sensor_mapping["0000"] = "NULL";
    sensor_mapping["0110"] = "W";
    sensor_mapping["0001"] = "N";
    sensor_mapping["1000"] = "S";
    sensor_mapping["0111"] = "WN";
    sensor_mapping["1110"] = "SW";
    sensor_mapping["1001"] = "SN";
    sensor_mapping["1111"] = "WNS";
  }
  // 1 st case bot facing SOUTH //
  else if (orientation_marker == 'S')
  {
    sensor_mapping["0000"] = "NULL";
    sensor_mapping["0110"] = "S";
    sensor_mapping["0001"] = "W";
    sensor_mapping["1000"] = "E";
    sensor_mapping["0111"] = "SW";
    sensor_mapping["1110"] = "ES";
    sensor_mapping["1001"] = "EW";
    sensor_mapping["1111"] = "SEW";
  }

  return sensor_mapping;
}
// void print(vector<vector<int>> &mat)
// {
//   for (int x = 0; x < mat.size(); x++)
//   {
//     for (int y = 0; y < mat[0].size(); y++)
//     {
//       cout << mat[x][y] << " ";
//     }
//     cout << endl;
//   }
// }
void initalize(vector<vector<int>> &mat, int m, int n)
{
  int mid = (floor(m / 2) - 1);
  for (int x = (mid + 2); x < m; x++)
  {
    mat[x][mid] = mat[x - 1][mid] + 1;
  }
  for (int x = (mid - 1); x >= 0; x--)
  {
    mat[x][mid] = mat[x + 1][mid] + 1;
  }
  for (int x = 0; x < m; x++)
  {
    for (int y = (mid - 1); y >= 0; y--)
    {
      mat[x][y] = mat[x][y + 1] + 1;
    }
  }
  for (int x = 0; x < m; x++)
  {
    mat[x][(mid + 1)] = mat[x][(mid)];
  }
  for (int x = 0; x < m; x++)
  {
    for (int y = (mid + 2); y < m; y++)
    {
      mat[x][y] = mat[x][y - 1] + 1;
    }
  }
  // print(mat);
}

void walls_update(vector<vector<string>> &walls, int curr_x_idx, int curr_y_idx, vector<int> sensors)
{
  // checking and updating oreientation each time while updating walls as well as
  // creating the corresponding map of walls on the basis of current orientation
  unordered_map<string, string> sensor_dict = mapping_sensor(sensors);
  string s = mapping_sensor_2(sensors);
  string movements = sensor_dict[s];
  walls[curr_x_idx][curr_y_idx] = movements;
}


vector<int> repopulate_sensors(int s1, int s2, int s3, int s4)
{
  vector<int> v = {s1, s2, s3, s4};
  return v;
}
bool check(int curr_xidx, int curr_yidx, int size)
{
  if ((curr_xidx < 0 || curr_xidx >= size) && (curr_yidx < 0 || curr_yidx >= size))
  {
    return false;
  }
  return true;
}
pair<int, char> access_neighbours_min(vector<vector<int>> &maze, int curr_xidx, int curr_yidx, vector<vector<string>> &walls)
{
  int mini = 10e6;
  char marker = 'X';
  string wall = walls[curr_xidx][curr_yidx];

  if (wall == "N")
  {
    if (check(curr_xidx, curr_yidx - 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx - 1];
      mini = min(mini, maze[curr_xidx][curr_yidx - 1]);
      if (mini == val)
      {
        marker = 'S';
      }
    }
    if (check(curr_xidx + 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx + 1][curr_yidx];
      mini = min(mini, maze[curr_xidx + 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'E';
      }
    }
    if (check(curr_xidx - 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx - 1][curr_yidx];
      mini = min(mini, maze[curr_xidx - 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'W';
      }
    }
    return {mini, marker};
  }
  else if (wall == "E")
  {
    if (check(curr_xidx - 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx - 1][curr_yidx];
      mini = min(mini, maze[curr_xidx - 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'W';
      }
    }

    if (check(curr_xidx, curr_yidx + 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx + 1];
      mini = min(mini, maze[curr_xidx][curr_yidx + 1]);
      if (mini == val)
      {
        marker = 'N';
      }
    }
    if (check(curr_xidx, curr_yidx - 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx - 1];
      mini = min(mini, maze[curr_xidx][curr_yidx - 1]);
      if (mini == val)
      {
        marker = 'S';
      }
    }
    return {mini, marker};
  }

  else if (wall == "S")
  {
    if (check(curr_xidx, curr_yidx + 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx + 1];
      mini = min(mini, maze[curr_xidx][curr_yidx + 1]);
      if (mini == val)
      {
        marker = 'N';
      }
    }
    if (check(curr_xidx + 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx + 1][curr_yidx];
      mini = min(mini, maze[curr_xidx + 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'E';
      }
    }
    if (check(curr_xidx - 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx - 1][curr_yidx];
      mini = min(mini, maze[curr_xidx - 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'W';
      }
    }
    return {mini, marker};
  }
  else if (wall == "W")
  {
    if (check(curr_xidx + 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx + 1][curr_yidx];
      mini = min(mini, maze[curr_xidx + 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'E';
      }
    }

    if (check(curr_xidx, curr_yidx + 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx + 1];
      mini = min(mini, maze[curr_xidx][curr_yidx + 1]);
      if (mini == val)
      {
        marker = 'N';
      }
    }
    if (check(curr_xidx, curr_yidx - 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx - 1];
      mini = min(mini, maze[curr_xidx][curr_yidx - 1]);
      if (mini == val)
      {
        marker = 'S';
      }
    }
    return {mini, marker};
  }
  else if (wall == "NE")
  {
    if (check(curr_xidx, curr_yidx - 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx - 1];
      mini = min(mini, maze[curr_xidx][curr_yidx - 1]);
      if (mini == val)
      {
        marker = 'S';
      }
    }
    if (check(curr_xidx - 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx - 1][curr_yidx];
      mini = min(mini, maze[curr_xidx - 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'W';
      }
    }
    return {mini, marker};
  }
  else if (wall == "NW")
  {
    if (check(curr_xidx, curr_yidx - 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx - 1];
      mini = min(mini, maze[curr_xidx][curr_yidx - 1]);
      if (mini == val)
      {
        marker = 'S';
      }
    }
    if (check(curr_xidx + 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx + 1][curr_yidx];
      mini = min(mini, maze[curr_xidx + 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'E';
      }
    }
    return {mini, marker};
  }
  else if (wall == "EW")
  {
    if (check(curr_xidx, curr_yidx + 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx + 1];
      mini = min(mini, maze[curr_xidx][curr_yidx + 1]);
      if (mini == val)
      {
        marker = 'N';
      }
    }
    if (check(curr_xidx, curr_yidx - 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx - 1];
      mini = min(mini, maze[curr_xidx][curr_yidx - 1]);
      if (mini == val)
      {
        marker = 'S';
      }
    }
    return {mini, marker};
  }
  else if (wall == "NEW")
  {
    if (check(curr_xidx, curr_yidx - 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx - 1];
      mini = min(mini, maze[curr_xidx][curr_yidx - 1]);
      if (mini == val)
      {
        marker = 'S';
      }
    }
    return {mini, marker};
  }
  // es,ns,ens
  else if (wall == "ES")
  {
    if (check(curr_xidx, curr_yidx + 1, maze.size()) == true)
    {
      int val = maze[curr_xidx][curr_yidx + 1];
      mini = min(mini, maze[curr_xidx][curr_yidx + 1]);
      if (mini == val)
      {
        marker = 'N';
      }
    }
    if (check(curr_xidx - 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx - 1][curr_yidx];
      mini = min(mini, maze[curr_xidx - 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'W';
      }
    }
    return {mini, marker};
  }
  else if (wall == "NS")
  {
    if (check(curr_xidx - 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx - 1][curr_yidx];
      mini = min(mini, maze[curr_xidx - 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'W';
      }
    }
    if (check(curr_xidx + 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx + 1][curr_yidx];
      mini = min(mini, maze[curr_xidx + 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'E';
      }
    }
    return {mini, marker};
  }
  else if (wall == "ENS")
  {
    if (check(curr_xidx - 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx - 1][curr_yidx];
      mini = min(mini, maze[curr_xidx - 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'W';
      }
    }
  }
  // sw,wns
  else if (wall == "SW")
  {
    if (check(curr_xidx, curr_yidx + 1, maze.size()) == true)
    {
      int val = maze[curr_xidx - 1][curr_yidx];
      mini = min(mini, maze[curr_xidx - 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'N';
      }
    }
    if (check(curr_xidx + 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx + 1][curr_yidx];
      mini = min(mini, maze[curr_xidx + 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'E';
      }
    }
    return {mini, marker};
  }
  else if (wall == "WNS")
  {
    if (check(curr_xidx + 1, curr_yidx, maze.size()) == true)
    {
      int val = maze[curr_xidx + 1][curr_yidx];
      mini = min(mini, maze[curr_xidx + 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'E';
      }
    }
    return {mini, marker};
  }
  // sew
  else if (wall == "SEW")
  {
    if (check(curr_xidx, curr_yidx + 1, maze.size()) == true)
    {
      int val = maze[curr_xidx - 1][curr_yidx];
      mini = min(mini, maze[curr_xidx - 1][curr_yidx]);
      if (mini == val)
      {
        marker = 'N';
      }
    }
    return {mini, marker};
  }
  return {mini, marker};
}

void add_neighbours(string wall, queue<pair<pair<int, int>, int>> &q, int curr_x_idx, int curr_y_idx, vector<vector<int>> &maze)
{
  if (wall == "N")
  {
    if (check(curr_x_idx, curr_y_idx - 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx - 1}, maze[curr_x_idx][curr_y_idx - 1]});
    }

    if (check(curr_x_idx + 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx + 1, curr_y_idx}, maze[curr_x_idx + 1][curr_y_idx]});
    }
    if (check(curr_x_idx - 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx - 1, curr_y_idx}, maze[curr_x_idx - 1][curr_y_idx]});
    }
  }
  else if (wall == "E")
  {
    if (check(curr_x_idx - 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx - 1, curr_y_idx}, maze[curr_x_idx - 1][curr_y_idx]});
    }

    if (check(curr_x_idx, curr_y_idx + 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx + 1}, maze[curr_x_idx][curr_y_idx + 1]});
    }
    if (check(curr_x_idx, curr_y_idx - 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx - 1}, maze[curr_x_idx][curr_y_idx - 1]});
    }
  }
  else if (wall == "W")
  {
    if (check(curr_x_idx + 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx + 1, curr_y_idx}, maze[curr_x_idx + 1][curr_y_idx]});
    }

    if (check(curr_x_idx, curr_y_idx + 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx + 1}, maze[curr_x_idx][curr_y_idx + 1]});
    }
    if (check(curr_x_idx, curr_y_idx - 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx - 1}, maze[curr_x_idx][curr_y_idx - 1]});
    }
  }
  else if (wall == "S")
  {
    if (check(curr_x_idx, curr_y_idx + 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx + 1}, maze[curr_x_idx][curr_y_idx + 1]});
    }
    if (check(curr_x_idx + 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx + 1, curr_y_idx}, maze[curr_x_idx + 1][curr_y_idx]});
    }
    if (check(curr_x_idx - 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx - 1, curr_y_idx}, maze[curr_x_idx - 1][curr_y_idx]});
    }
  }
  else if (wall == "NE")
  {
    if (check(curr_x_idx, curr_y_idx - 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx - 1}, maze[curr_x_idx - 1][curr_y_idx]});
    }
    if (check(curr_x_idx - 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx - 1, curr_y_idx}, maze[curr_x_idx - 1][curr_y_idx]});
    }
  }
  else if (wall == "NW")
  {
    if (check(curr_x_idx, curr_y_idx - 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx - 1}, maze[curr_x_idx][curr_y_idx - 1]});
    }
    if (check(curr_x_idx + 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx + 1, curr_y_idx}, maze[curr_x_idx + 1][curr_y_idx]});
    }
  }
  else if (wall == "EW")
  {
    if (check(curr_x_idx, curr_y_idx + 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx + 1}, maze[curr_x_idx][curr_y_idx + 1]});
    }
    if (check(curr_x_idx, curr_y_idx - 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx - 1}, maze[curr_x_idx][curr_y_idx - 1]});
    }
  }
  else if (wall == "NEW")
  {
    if (check(curr_x_idx, curr_y_idx - 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx - 1}, maze[curr_x_idx][curr_y_idx - 1]});
    }
  }

  else if (wall == "ES")
  {
    if (check(curr_x_idx, curr_y_idx + 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx + 1}, maze[curr_x_idx][curr_y_idx + 1]});
    }
    if (check(curr_x_idx - 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx - 1, curr_y_idx}, maze[curr_x_idx - 1][curr_y_idx]});
    }
  }
  else if (wall == "NS")
  {
    if (check(curr_x_idx - 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx - 1, curr_y_idx}, maze[curr_x_idx - 1][curr_y_idx]});
    }
    if (check(curr_x_idx + 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx + 1, curr_y_idx}, maze[curr_x_idx + 1][curr_y_idx]});
    }
  }
  else if (wall == "ENS")
  {
    if (check(curr_x_idx - 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx - 1, curr_y_idx}, maze[curr_x_idx - 1][curr_y_idx]});
    }
  }
  else if (wall == "SW")
  {
    if (check(curr_x_idx - 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx - 1, curr_y_idx}, maze[curr_x_idx - 1][curr_y_idx]});
    }
    if (check(curr_x_idx - 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx - 1, curr_y_idx}, maze[curr_x_idx - 1][curr_y_idx]});
    }
  }
  else if (wall == "WNS")
  {
    if (check(curr_x_idx + 1, curr_y_idx, maze.size()) == true)
    {
      q.push({{curr_x_idx + 1, curr_y_idx}, maze[curr_x_idx + 1][curr_y_idx]});
    }
  }
  else if (wall == "SEW")
  {
    if (check(curr_x_idx, curr_y_idx + 1, maze.size()) == true)
    {
      q.push({{curr_x_idx, curr_y_idx + 1}, maze[curr_x_idx][curr_y_idx + 1]});
    }
  }
}

void flood_fill(vector<vector<string>> &walls, vector<int> &sensors, int &x_idx, int &y_idx, int m, vector<vector<int>> &maze,char current_orientation)
{
  int size = (floor(m / 2) - 1);
  // condition for termination after we have reached the central node//
  while (x_idx != size && y_idx != size)
  {
    // Repopulation of data//
    vector<int>sensors2 = repopulate_sensors(sensors[2], sensors[0], sensors[1], sensors[3]);
    // Wall updation//

    walls_update(walls, x_idx, y_idx, sensors2);
    // Accessing all the presently accesible neighbours//
    pair<int, char> p = access_neighbours_min(maze, x_idx, y_idx, walls);
    if (p.first == 0)
    {
      // Destination reached //
      return;
    }
    else
    {
      int curr_cell_val = maze[x_idx][y_idx];
      if (curr_cell_val < p.first)
      {
        // if the minimum of all accessible cells
        // greater than current then reflooding required
        reflooding(maze, walls, x_idx, y_idx, maze.size());
      }
      else if (curr_cell_val >= p.first)
      {
        // if the maximum of all accessible cells
        // lesser than current then move to minimum
        //updating the current orientation//
        char marker = p.second;
        if (marker == 'N')
        {
          // move north//
          if(current_orientation == 'N'){
            straight();
          }
          else if(current_orientation == 'S'){
            u_turn();
            straight();
          }
          else if(current_orientation == 'E'){
            left_turn();
            straight();
          }
          else if(current_orientation == 'W'){
            right_turn();
            straight();
          }
          y_idx+=1;
          current_orientation = 'N';
        }
        else if (marker == 'S')
        {
          // move south//
          if(current_orientation == 'N'){
            u_turn();
            straight();
          }
          else if(current_orientation == 'S'){
            straight();
          }
          else if(current_orientation == 'E'){
            right_turn();
            straight();
          }
          else if(current_orientation == 'W'){
            left_turn();
            straight();
          }
          y_idx -= 1;
          current_orientation = 'S';
        }
        else if (marker == 'E')
        {
          if(current_orientation == 'N'){
            right_turn();
            straight();
          }
          else if(current_orientation == 'S'){
            left_turn();
            straight();
          }
          else if(current_orientation == 'E'){
            straight();
          }
          else if(current_orientation == 'W'){
            u_turn();
            straight();
          }
          x_idx += 1;
          current_orientation = 'E';
        }
        else if(marker == 'W'){
          //move west//
          if(current_orientation == 'N'){
            left_turn();
            straight();
          }
          else if(current_orientation == 'S'){
            right_turn();
            straight();
          }
          else if(current_orientation == 'E'){
            u_turn();
            straight();
          }
          else if(current_orientation == 'W'){
            straight();
          }
          x_idx-=1;
          current_orientation = 'W';
        }
        /*
        [curr_xidx + 1][curr_yidx]=l
        [curr_xidx][curr_yidx + 1]=r
        [curr_xidx - 1][curr_yidx]=f
        */
      }
    }
  }
}

void reflooding(vector<vector<int>> &maze, vector<vector<string>> &walls, int curr_x_idx, int curr_y_idx, int size)
{
  queue<pair<pair<int, int>, int>> q;
  q.push({{curr_x_idx, curr_x_idx}, maze[curr_x_idx][curr_y_idx]});
  while (q.empty() != true)
  {
    auto p = q.front();
    q.pop();
    pair<int, int> indexes = p.first;
    int curr_heuristic = p.second;
    string wall = walls[indexes.first][indexes.second];
    pair<int, char> p_2 = access_neighbours_min(maze, curr_x_idx, curr_y_idx, walls);
    int minimum = p_2.first;
    if (minimum >= maze[curr_x_idx][curr_y_idx])
    {
      maze[indexes.first][indexes.second] = minimum + 1;
      add_neighbours(wall, q, curr_x_idx, curr_y_idx, maze);
    }
    else
    {
      continue;
    }
  }
}


// function calculating distance with Ultrasonic sensor 
int ultrasonic(int trigpin,int echopin){
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  int duration = pulseIn(echopin, HIGH);// measure duration of pulse from ECHO pin
  int distance = (0.0343 * duration)/2; // calculate the distance
   Serial.print("distance1: ");
  Serial.print(distance1_cm);
  Serial.println(" cm");
  Serial.print("distance1: ");
  Serial.print(distance2_cm);
  Serial.println(" cm");
  delay(500);
  return distance;
}

void motor_init(int motorA,int motorB,int enable) {
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(enable, OUTPUT);
  digitalWrite(motorA, LOW);
  digitalWrite(motorB, LOW);
  analogWrite(enable, LOW);
}

void forward(){
  analogWrite(ENABLE_1, 150);
  analogWrite(ENABLE_2, 150);
  digitalWrite(MOTOR1_A , HIGH);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , HIGH);
  digitalWrite(MOTOR2_B , LOW);
}

void stop(){
  digitalWrite(MOTOR1_A , LOW);
  digitalWrite(MOTOR1_B , LOW);
  digitalWrite(MOTOR2_A , LOW);
  digitalWrite(MOTOR2_B , LOW);
}

void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  motor_init(MOTOR1_A,MOTOR1_B,ENABLE_1);
  motor_init(MOTOR2_A,MOTOR2_B,ENABLE_2);

  int value1 = digitalRead(ir1);
  int value2 = digitalRead(ir2);
  int value3 = digitalRead(ir3);
  int value4 = digitalRead(ir4);

  initalize(mat, m, n);

}

void loop() {
  distance1_cm = ultrasonic(trigPin1,echoPin1);// distance from left wall
  distance2_cm = ultrasonic(trigPin2,echoPin2);// distance for right wall
  forward();
  delay(200);
  stop();

  vector<int>sensors = repopulate_sensors(value3, value1, value2, value4);
  flood_fill(walls, sensors, x, y, 16, maze, orientation_marker);
}
  //front is 00
//   if(!value1 && !value2){
//     if(value3 && value4){
//       if(distance1_cm == distance2_cm){
//         direction(150,150);
//       }
//       else if(distance1_cm < distance2_cm){
//         direction(200,150);// speed change
//       }
//       else if(distance1_cm > distance2_cm){
//         direction(150,200);// speed change 
//       }
//     }
//     else if(!value3 && value4){
//       direction(20,50);// 90 degree rotation for turning left
//     } 
//     else if(value3 && !value4){
//       direction(50,20);// rotation towards right
//     }
//   }
//   else if(value1 && value2){
//     if(!value3 && value4){
//       direction(20,50);// 90 degree rotation for turning left
//     } 
//     else if(!value3 && value4){
//       direction(50,20);// rotation towards right
//     }
//     else if(value3 && value4){
//       stop();
//       direction(60,10);
//     }
//   } 
// }


/*
 ---------------------------------FLOW-OF-DATA and ACTION-----------------------------------------------------------------------
1)heuristic values.
2)vector of corresponding movements.

conditions for updation and re-flooding.

3)Updating the walls-: walls structure will consist of (n x n) size of maze where
the cell will contain a string representing possible movements.
4)Re-flooding condition - True or false.
    1)if true then re-flood the maze and recalculate the manhatten distances from the center.
    2)if false then continue the movements towards the minimum of accesible neighbours.
5)Re-flooding can be done through the approach of BFS like and updation of heuristic values by minimum + 1.
6)Re-flooding condtion -: if the min({all possible accesible neighbours}) >= curr_node value then move to a
possible direction.
*/





























































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































