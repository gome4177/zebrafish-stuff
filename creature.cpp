#include"genome.cpp"
#include"network.cpp"

/*Again, step within creature
 * 0 normal
 * 1 brownian
 * 2 random vector
 */

#define PI 3.14156

class creature{
  private:
    int food_collected;
    int num_gametes;
    double x,y;
    double speed;
    double last_x, last_y;
    double avgx, avgy;
    double avg_speed;
    double foodx, foody;
    double varx,vary,varspeed;
    double inputs[input_size];
    double outputs[output_size];
    network brain;
    double fitness;
    int step_num;
    bool dead;  // dead creatures continue to move to collect data, but don't produce gametes
    double rnd_vector;

  public:
    genome g;
    creature();
    void reset();
    void create(creature,creature);
    void create(chromosome,chromosome);
    void copy(creature);
    void set_dead(bool b){dead = b;}
    bool step(double,double,vector<chromosome *>  *,int);
    bool step_random(double,double,vector<chromosome *> *);
    void fitness_to_gametes(vector<chromosome *> *);
    double getX() {return x;}
    double getY() {return y;}
    double getSpeed() {return speed;}  
    void print() {g.print();}
    int get_num_gametes() {return num_gametes;}
    void removeGamete() {num_gametes--;}
    double get_avg_speed(){return avg_speed;}
    double get_avg_x(){return avgx;}
    double get_avg_y(){return avgy;}
    double get_food(){return food_collected;}
    double get_var_x(){return varx;}
    double get_var_y(){return vary;}
    double get_var_speed(){return varspeed;}
    void display();
    void runbrain();
    void set_inputs();
    void mutate();
    chromosome getMaternal() {return g.getMaternal();}
    chromosome getPaternal() {return g.getPaternal();}
};  

  creature::creature(){
      rnd_vector = -1;
      reset();
  }
  

  void creature::reset(){
    food_collected = 0;
    num_gametes = 0;
//    g.mutate();
    brain.set_weights(g);  
    x = last_x = width/2.0;
    y = last_y = height/2.0;
    for(int i = 0; i < output_size; i++){  // zero outputs for recurrance
      outputs[i] = 0;
    }
    fitness = 0;
    avgx = avgy = avg_speed = 0;
    step_num = 0;
    dead = false;
  }

  void creature::create(creature c1,creature c2){
     g.create(c1.getMaternal(),c2.getPaternal());
     reset();
  }  

  void creature::mutate(){
    g.mutate();
  }
  
  void creature::create(chromosome c1,chromosome c2){
     g.create(c1,c2);
  }  

  void creature::copy(creature c1){
    g.create(c1.getMaternal(),c1.getPaternal());
  }

  double range_random(double bottom, double top) {
    double created_random = bottom + (((double)rand())*(top-bottom))/(RAND_MAX+1.0);
    return created_random;
  }

  bool creature::step_random(double fx, double fy, vector<chromosome *> *vg) {
     double distance_food;
     foodx = fx;
     foody = fy;
     last_x = x;
     last_y = y;
     distance_food = sqrt((foodx-x)*(foodx-x) + (foody-y)*(foody-y));

     speed =  ( sqrt( (last_x-x)*(last_x-x) + (last_y-y)*(last_y-y) ));
     avgx += x/time_steps;
     avgy += y/time_steps;
     avg_speed += ( speed / time_steps);
     step_num++;
     if(food_present && (distance_food < food_range)){
	if(!dead){ // dead creatures don't collect food or generate gametes
//cout << "  " << distance_food << endl;
	        food_collected++;
		chromosome *temp;
		for(int i = 0; i < num_gametes_per_food; i++){
	  	  temp = new chromosome();
		  temp->copy(g.getGamete());
		  vg->push_back(temp);
        	}
        	num_gametes+=num_gametes_per_food;
	}
//      cout << "Food: " << x << "," << y << "    " << foodx <<","<< foody << endl;
        return true;
     }
    return false;

  }



bool creature::step(double fx, double fy, vector<chromosome *> *vg, int gen_random){
     double distance_food;
     foodx = fx;
     foody = fy;
     last_x = x;
     last_y = y;
     distance_food = sqrt((foodx-x)*(foodx-x) + (foody-y)*(foody-y));
     set_inputs();
     runbrain();
     
/*
if(food_present){
cout << " " << food_present << " " << distance_food << "     " ;
for(int i =0; i < 12; i++){
   cout << inputs[i] << " ";
}
cout << "    " << outputs[0] << " " << outputs[1];
cout << endl;
}
*/
     if (gen_random==1) {
        x += range_random(food_range*-1.0, food_range);
        y += range_random(food_range*-1.0, food_range);
     } else if (gen_random == 2) {
         //Code for random vector
         //If vector is -1 (pick a vector out) or if x or y is zero pick a new vector
        if (rnd_vector == -1 || x == 0 || x == width || y == 0 || y == height) {
            rnd_vector = range_random(0, 2*PI);
        }

        double rnd_len = range_random(0, food_range);
        x += rnd_len*cos(rnd_vector);
        y += rnd_len*sin(rnd_vector);     

        
     } else {
        x += food_range*outputs[0];
        y += food_range*outputs[1];
     }
   
    //Going over the food range
/*    if (sqrt(pow(x-last_x, 2) + pow(y-last_y, 2)) > food_range) {
        //std::cout << x << "   " << last_x  << "    " << y << "   " << last_y <<  " 1 " << std::endl;
        double rads = atan2(y-last_y, x-last_x);
        x = cos(rads) * food_range + last_x;
        y = sin(rads) * food_range + last_y;
        //std::cout << x << "   " << last_x  << "    " << y << "   " << last_y <<  " 2 " << std::endl;
    }
*/

    if(x < 0)
        x = 0;
     if(x > width)
        x = width;
     if (y < 0)
        y = 0;
     if (y > height)
        y = height;

     speed =  ( sqrt( (last_x-x)*(last_x-x) + (last_y-y)*(last_y-y) ));
     avgx += x/time_steps;
     avgy += y/time_steps;
     avg_speed += ( speed / time_steps);
     step_num++;

     fitness += 10.0/(1.0+(distance_food*distance_food));
     if(food_present && (distance_food < food_range)){

	if(!dead){ // dead creatures don't collect food or generate gametes
//cout << "  " << distance_food << endl;
	        food_collected++;
         chromosome *temp;
		for(int i = 0; i < num_gametes_per_food; i++){
	  	  temp = new chromosome();
		  temp->copy(g.getGamete());
		  vg->push_back(temp);
        	}
        	num_gametes+=num_gametes_per_food;
	}
//      cout << "Food: " << x << "," << y << "    " << foodx <<","<< foody << endl;
        return true;
     }
     return false;
  }

  void creature::fitness_to_gametes(vector<chromosome *> *vg){
     if(!useFitness){  // useFitness is a flag for fitness
        return;
     }
     chromosome *temp;
     cout << "fitness: " << food_collected << " " << fitness << "\n";
     while(fitness > 0){
        temp = new chromosome();
        temp->copy(g.getGamete());
        vg->push_back(temp);
	fitness--;
     }
  }
     
  
  void creature::runbrain(){
    brain.run(inputs,outputs); 
  }

  void creature::set_inputs(){
    inputs[0] = 1;  // bias
    double d = sqrt ( (foodx-x)*(foodx-x) + (foody-y)*(foody-y));
    if(food_present && (d < sensing_range)){
       inputs[1] = 10.0*(foodx - x)/double(sensing_range);  
       inputs[2] = 10.0*(foody - y)/double(sensing_range);   
//       inputs[1] = (foodx - x);  
//       inputs[2] = (foody - y);   
    }
    else{
       inputs[1] = 0;  
       inputs[2] = 0;   
    }
   
   /* inputs[3] = 0;  // predator x - doesn't matter
    inputs[4] = 0;  // predator
    if(predator){  
	inputs[4] = y;  // distance to predator at surface
    }
    inputs[5] =  1/(1+food_collected);
    inputs[6] =  x/double(width);
    inputs[7] =  y/double(height);
    inputs[8] = (width - x)/double(width);
    inputs[9] = (height-y)/double(height);
//    inputs[10] = 10*outputs[0];  // recurrent
//    inputs[11] = 10*outputs[1];  // recurrent
    */
  }

  void creature::display(){
    cout << x << " " << y << endl;
  }



