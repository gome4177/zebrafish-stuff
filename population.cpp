#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;
#include"creature.cpp"
#include"food.cpp"
/*gen_random is now an integer
 * 0 cooresponds to a non-random run
 * 1 cooresponds to brownian motion
 * 2 cooresponds to random vector until it hits the a side,
 * then another random vector, etc.*/

string to_string(int);
int gen_random = 0;
class population{
  private:
    creature the_pop[pop_size];
    double foodx, foody;
    int food_counter;
    int closest_food;  // keeps track of the closest food to the creature
    vector<chromosome *> gamete_pool;
    double avg_speed,avg_x,avg_y,avg_food;
    double popavg_speed,popavg_x,popavg_y, popavg_food;
    vector<food *> food_list;
    ofstream avgoutputfile;
    ofstream avgavgoutputfile;
    ofstream avgfoodlessoutputfile;
    ofstream avgavgfoodlessoutputfile;
    ofstream avgbrownoutputfile;
    ofstream avgrandomoutputfile;
    ofstream avgavgbrownoutputfile;
    ofstream avgavgrandomoutputfile;
    ofstream genomefile;

//    ofstream avgoutputfilefoodless;
    double x_values[time_steps];
    double y_values[time_steps];
    double speed_values[time_steps];
  public:
    population();
    void run(int);
    void run_no_food(int);
    void run_brownian(int);
    void run_random(int);
    void reset_food();
    void update_food();
    void next_gen();
    void collectdata();
    void step_creature(int,int);
    void set_closest_food(double,double);
    void calc_stats();
    void calc_stats_foodless();
    void calc_stats_random();
    void calc_stats_brownian();
    void print();
    void close_datafiles();
//    void end_of_trial();
//    void resetCurrent();
//    void step();
//    void setCreaturesFoodVector();
//    void collectData();
//    void next_generation();
//    void prepare_gen_data();

    
};

  population::population(){
    avg_speed = avg_x = avg_y = avg_food = 0;
    popavg_x = popavg_y = popavg_speed = popavg_food = 0;
    string avgoutfilename;
    string avgavgfilename;
    string avgavgoutfilename_random;
    string avgavgoutfilename_brown;
    string avgoutfilename_random;
    string avgoutfilename_brown;
    string outfilename_genome;

    outfilename_genome = "genome";
    outfilename_genome += to_string(trial);
    outfilename_genome += ".txt";

    genomefile.close();
    genomefile.open(outfilename_genome.c_str());
    genomefile << "generation, creature, ";

      for (int i = 0; i < num_weights; i++) {
          genomefile << "weight" << i;
          if (num_weights -1 != i) {
              genomefile << ", ";
          }
      }
    genomefile << endl;
    avgoutfilename = "foodaverages";
    avgoutfilename += to_string(trial);
    avgoutfilename += ".txt";

    avgavgfilename = "foodavgavg";
    avgavgfilename += to_string(trial);
    avgavgfilename += ".txt";

    avgavgoutputfile.close();
    avgavgoutputfile.open(avgavgfilename.c_str());
    avgavgoutputfile << "popavg_speed, popavg_x, popavg_y, popavg_food" << endl;
    

    avgoutputfile.close();
    avgoutputfile.open(avgoutfilename.c_str());
    avgoutputfile << "trial, generation, treatment, food/nofood, network,  x, var x, y, var y, speed, var speed, food collected\n"; 

// foodless files
    string avgfoodlessoutfilename;
    string avgavgfoodlessfilename;
    avgfoodlessoutfilename = "foodlessaverages";
    avgfoodlessoutfilename += to_string(trial);
    avgfoodlessoutfilename += ".txt";

    avgavgfoodlessfilename = "foodlessavgavg";
    avgavgfoodlessfilename += to_string(trial);
    avgavgfoodlessfilename += ".txt";

    avgavgoutfilename_brown = "brownainavgavg";
    avgavgoutfilename_brown += to_string(trial);
    avgavgoutfilename_brown += ".txt";

    avgavgbrownoutputfile.close();
    avgavgbrownoutputfile.open(avgavgoutfilename_brown.c_str());
    avgavgbrownoutputfile << "popavg_speed, popavg_x, popavg_y, popavg_food" << endl;
    
    avgoutfilename_brown = "brownainaverages";
    avgoutfilename_brown += to_string(trial);
    avgoutfilename_brown += ".txt";
    
    avgbrownoutputfile.close();
    avgbrownoutputfile.open(avgoutfilename_brown.c_str());
    avgbrownoutputfile << "trial, generation, treatment, food/nofood, network, x, var x, y, var y, speed, var speed, food collected\n"; 

    avgoutfilename_random = "randomaverages";
    avgoutfilename_random += to_string(trial);
    avgoutfilename_random += ".txt";

    avgrandomoutputfile.close();
    avgrandomoutputfile.open(avgoutfilename_random.c_str());
    avgrandomoutputfile << "trial, generation, treatment, food/nofood, network, x, var x, y, var y, speed, var speed, food collected\n"; 

    avgavgoutfilename_random = "randomavgavg";
    avgavgoutfilename_random += to_string(trial);
    avgavgoutfilename_random += ".txt";

    avgavgrandomoutputfile.close();
    avgavgrandomoutputfile.open(avgavgoutfilename_random.c_str());
    avgavgrandomoutputfile << "popavg_speed, popavg_x, popavg_y, popavg_food" << endl;


    avgavgfoodlessoutputfile.close();
    avgavgfoodlessoutputfile.open(avgavgfoodlessfilename.c_str());
    avgavgfoodlessoutputfile << "popavg_speed, popavg_x, popavg_y, popavg_food" << endl;
    


    avgfoodlessoutputfile.close();
    avgfoodlessoutputfile.open(avgfoodlessoutfilename.c_str());
    avgfoodlessoutputfile << "trial, generation, treatment, food/nofood, network, x, var x, y, var y, speed, var speed, food collected\n"; 
 
   reset_food();
  }
  
  void population::print(){
    the_pop[0].print();
cout << endl;
    the_pop[1].print();
cout << endl;
    the_pop[2].print();
cout << endl;
    the_pop[3].print();
  }

  void population::close_datafiles(){
    avgavgoutputfile.close();
    avgoutputfile.close();
    avgavgfoodlessoutputfile.close();
    avgfoodlessoutputfile.close();
    avgrandomoutputfile.close();
    avgbrownoutputfile.close();
    avgavgrandomoutputfile.close();
    avgavgbrownoutputfile.close();
    genomefile.close();
  }

  void population::reset_food(){
        food *f;
        for (int i = 0; i < food_list.size(); i++) {
            //std::cout << "okay" << std::endl;
            delete food_list[i];
            //std::cout << "okay okay" << std::endl;
            food_list[i] = NULL;
        }
        
        food_list.clear();
	    food_counter = 0;  // used for falling food, to add some occasionally
        
        switch(treatment){
		case 1:
			for(int i = 0; i < food_amount; i++){
            			f = new food();
				        f->anywhere();
            			food_list.push_back(f);
			}
			break;
		case 2:
			for(int i = 0; i < food_amount; i++){
            			f = new food();
				        f->top();
            			food_list.push_back(f);
			}
			break;
		case 3:
			for(int i = 0; i < food_amount; i++){
            			f = new food();
			        	f->bottom();
            			food_list.push_back(f);
			}
			break;
		case 5:
            		f = new food();
			        f->falling();
            		food_list.push_back(f);
			break;
        case 6:
			for(int i = 0; i < food_amount; i++){
            			f = new food();
			        	f->anywhere();
            			food_list.push_back(f);
            }
            break;
		default:
			cout << "Unknown food case!" << endl;
        }
  } 

  void population::update_food(){
	if(treatment == 5){
		for(int i = 0; i < food_list.size(); i++){
		      if(food_list[i]->fall() == 0){
                    //std::cout << "okay" << std::endl;
                    delete food_list[i];
                    //std::cout << "okay okay" << std::endl;
                    food_list[i] = NULL;
		   	        food_list.erase(food_list.begin()+i);
			    }	
		}
		if(food_counter % 2 == 0 && food_counter < 2*food_amount){  // every other timestep add a food
            		food *f = new food();
			        f->falling();
            		food_list.push_back(f);
		}
		food_counter++;
	} else if (treatment == 6) {
        for (int i = 0; i < food_list.size(); i++) {
            food_list[i]->move();
        }
    }
  }

  void population::set_closest_food(double cx, double cy){
       double d,dmin,x,y;
       closest_food = 0;
       if(food_list.size() == 0){
	        closest_food = -1;
            return;
       }
       dmin = (food_list[0]->x - cx)*(food_list[0]->x - cx) + (food_list[0]->y - cy)*(food_list[0]->y -cy);
       for(int i = 1; i < food_list.size(); i++){
           if (food_list[i] != NULL) {
           d = (food_list[i]->x - cx)*(food_list[i]->x - cx) + (food_list[i]->y - cy)*(food_list[i]->y -cy);
           if(d < dmin){
                dmin = d;
		        closest_food = i;
           }
           }
       }
  }

 void population::calc_stats(){
 //   double avg_fish_x, avg_fish_y, avg_fish_speed;
    double var_fish_x, var_fish_y, var_fish_speed;
    avg_x = avg_y = avg_speed = 0;
    var_fish_x = var_fish_y = var_fish_speed = 0;
    for(int i = 0; i < time_steps; i++){
	avg_x += x_values[i];	
	avg_y += y_values[i];	
	avg_speed += speed_values[i];	
    }
    avg_x /= time_steps;
    avg_y /= time_steps;
    avg_speed /= time_steps;
    for(int i = 0; i < time_steps; i++){
	var_fish_x += ((x_values[i]-avg_x)*(x_values[i]-avg_x))/time_steps;
	var_fish_y += ((y_values[i]-avg_y)*(y_values[i]-avg_y))/time_steps;
	var_fish_speed += ((speed_values[i]-avg_speed)*(speed_values[i]-avg_speed))/time_steps;
    }
    popavg_x += avg_x;  
    popavg_y += avg_y;
    popavg_speed += avg_speed;
    avgoutputfile << avg_x << ", "<< var_fish_x << ", ";
    avgoutputfile << avg_y << ", "<< var_fish_y << ", ";
    avgoutputfile << avg_speed << ", "<< var_fish_speed << ", ";
 }

 void population::calc_stats_brownian(){
 //   double avg_fish_x, avg_fish_y, avg_fish_speed;
    double var_fish_x, var_fish_y, var_fish_speed;
    avg_x = avg_y = avg_speed = 0;
    var_fish_x = var_fish_y = var_fish_speed = 0;
    for(int i = 0; i < time_steps; i++){
	avg_x += x_values[i];	
	avg_y += y_values[i];	
	avg_speed += speed_values[i];	
    }
    avg_x /= time_steps;
    avg_y /= time_steps;
    avg_speed /= time_steps;
    for(int i = 0; i < time_steps; i++){
	var_fish_x += ((x_values[i]-avg_x)*(x_values[i]-avg_x))/time_steps;
	var_fish_y += ((y_values[i]-avg_y)*(y_values[i]-avg_y))/time_steps;
	var_fish_speed += ((speed_values[i]-avg_speed)*(speed_values[i]-avg_speed))/time_steps;
    }
    popavg_x += avg_x;  
    popavg_y += avg_y;
    popavg_speed += avg_speed;
    avgbrownoutputfile << avg_x << ", "<< var_fish_x << ", ";
    avgbrownoutputfile << avg_y << ", "<< var_fish_y << ", ";
    avgbrownoutputfile << avg_speed << ", "<< var_fish_speed << ", ";
 }

 void population::calc_stats_random(){
 //   double avg_fish_x, avg_fish_y, avg_fish_speed;
    double var_fish_x, var_fish_y, var_fish_speed;
    avg_x = avg_y = avg_speed = 0;
    var_fish_x = var_fish_y = var_fish_speed = 0;
    for(int i = 0; i < time_steps; i++){
	avg_x += x_values[i];	
	avg_y += y_values[i];	
	avg_speed += speed_values[i];	
    }
    avg_x /= time_steps;
    avg_y /= time_steps;
    avg_speed /= time_steps;
    for(int i = 0; i < time_steps; i++){
	var_fish_x += ((x_values[i]-avg_x)*(x_values[i]-avg_x))/time_steps;
	var_fish_y += ((y_values[i]-avg_y)*(y_values[i]-avg_y))/time_steps;
	var_fish_speed += ((speed_values[i]-avg_speed)*(speed_values[i]-avg_speed))/time_steps;
    }
    popavg_x += avg_x;  
    popavg_y += avg_y;
    popavg_speed += avg_speed;
    avgrandomoutputfile << avg_x << ", "<< var_fish_x << ", ";
    avgrandomoutputfile << avg_y << ", "<< var_fish_y << ", ";
    avgrandomoutputfile << avg_speed << ", "<< var_fish_speed << ", ";
 }


 void population::calc_stats_foodless(){
 //   double avg_fish_x, avg_fish_y, avg_fish_speed;
    double var_fish_x, var_fish_y, var_fish_speed;
    avg_x = avg_y = avg_speed = 0;
    var_fish_x = var_fish_y = var_fish_speed = 0;
    for(int i = 0; i < time_steps; i++){
	avg_x += x_values[i];	
	avg_y += y_values[i];	
	avg_speed += speed_values[i];	
    }
    avg_x /= time_steps;
    avg_y /= time_steps;
    avg_speed /= time_steps;
    for(int i = 0; i < time_steps; i++){
	var_fish_x += ((x_values[i]-avg_x)*(x_values[i]-avg_x))/time_steps;
	var_fish_y += ((y_values[i]-avg_y)*(y_values[i]-avg_y))/time_steps;
	var_fish_speed += ((speed_values[i]-avg_speed)*(speed_values[i]-avg_speed))/time_steps;
    }
    popavg_x += avg_x;  
    popavg_y += avg_y;
    popavg_speed += avg_speed;
    avgfoodlessoutputfile << avg_x << ", "<< var_fish_x << ", ";
    avgfoodlessoutputfile << avg_y << ", "<< var_fish_y << ", ";
    avgfoodlessoutputfile << avg_speed << ", "<< var_fish_speed << ", ";
 }


void population::run(int generation){
    //run_no_food(generation);
    //run_brownian(generation);
    //run_random(generation);
    double distance_to_p,dx,dy; // predator
    double predsig;//predator sigmoid
    food_present = true;
    avg_speed = avg_x = avg_y = avg_food = 0;

    for(int c = 0; c < pop_size; c++){
      reset_food();
      the_pop[c].reset();
      
      for(int t = 0; t < time_steps; t++){
	set_closest_food(the_pop[c].getX(),the_pop[c].getY());
         if(closest_food == -1){ // no food left
	//	break;
	 }
         step_creature(c, gen_random);
	 distance_to_p = double(the_pop[c].getY());//height;	 	 
	 // cout << t<<endl;
	 if ( chance(i/(1+(pow(e,(ro*distance_to_p-ro*corn))))+a )){  //sigmoid variables are defined in params.h 
	 // if ((i/(1+(pow(e,(ro*distance_to_p-ro*corn))))+a) >( random(1000%1000))){// earlier version of sigmoid fct, didnt work well  
	     cout << "  "  << c <<" died "<<the_pop[c].getY() << " "<< t<< " "<<the_pop[c].get_food()<<endl;
	      the_pop[c].set_dead(true);
	         next_gen();
	 }
	  
         x_values[t] = the_pop[c].getX();
         y_values[t] = the_pop[c].getY();
         speed_values[t] = the_pop[c].getSpeed();
	    if(treatment == 5 || treatment == 6){  // falling food
		    update_food();
	    }
	 
      avgoutputfile << trial << ", " << generation << ", " << treatment << ", Food, Network, ";
      calc_stats();  // add stats to the file
      avgoutputfile << the_pop[c].get_food() << "\n";
      popavg_food += the_pop[c].get_food();
      
      genomefile << generation << ", " << c << ", ";

      for (int i = 0; i < num_weights; i++) {
          genomefile << the_pop[c].g.getWeight(i);
          if (num_weights -1 != i) {
              genomefile << ", ";
	  }
      }
      genomefile << endl;
      }//end timesteps loop
//      the_pop[c].fitness_to_gametes(&gamete_pool);
    }   // end of creatures loop
    popavg_x /= pop_size;
    popavg_y /= pop_size;
    popavg_speed /= pop_size;
    popavg_food /= pop_size;
    avgavgoutputfile << popavg_speed << ", " << popavg_x <<", " << popavg_y << ", " <<  popavg_food << endl;
    // cout << popavg_food<<"\n";
    next_gen();
}
/*
void population::run_no_food(int generation){
    food_present = false;
    avg_speed = avg_x = avg_y = avg_food = 0;

    for(int c = 0; c < pop_size; c++){
//      reset_food();
      the_pop[c].reset();
      
      for(int t = 0; t < time_steps; t++){
         step_creature(c, gen_random);
         x_values[t] = the_pop[c].getX();
         y_values[t] = the_pop[c].getY();
         speed_values[t] = the_pop[c].getSpeed();
      }
      avgfoodlessoutputfile << trial << ", " << generation << ", " << treatment << ", NoFood, Network, ";
      calc_stats_foodless();  // add stats to the file
      avgfoodlessoutputfile << the_pop[c].get_food() << "\n";
      popavg_food += the_pop[c].get_food();
//      the_pop[c].fitness_to_gametes(&gamete_pool);
    }   // end of creatures loop
    popavg_x /= pop_size;
    popavg_y /= pop_size;
    popavg_speed /= pop_size;
    popavg_food /= pop_size;
    avgavgfoodlessoutputfile << popavg_speed << ", " << popavg_x <<", " << popavg_y << ", " <<  popavg_food << endl;
//cout << popavg_speed << ", " << popavg_x <<", " << popavg_y << ", " <<  popavg_food << endl;
   // next_gen();
  }
*/
  void population::run_random(int generation){
    food_present = true;
    int gen_random = 2;

    avg_speed = avg_x = avg_y = avg_food = 0;
    for(int c = 0; c < pop_size; c++){
      reset_food();
      the_pop[c].reset();
      
      for(int t = 0; t < time_steps; t++){
         step_creature(c, gen_random);
         x_values[t] = the_pop[c].getX();
         y_values[t] = the_pop[c].getY();
         speed_values[t] = the_pop[c].getSpeed();
      }
      avgrandomoutputfile << trial << ", " << generation << ", " << treatment << ", Food, Random_Vect, ";
      calc_stats_random();  // add stats to the file
      avgrandomoutputfile << the_pop[c].get_food() << "\n";
      popavg_food += the_pop[c].get_food();
      the_pop[c].fitness_to_gametes(&gamete_pool);
    }   // end of creatures loop
    popavg_x /= pop_size;
    popavg_y /= pop_size;
    popavg_speed /= pop_size;
    popavg_food /= pop_size;

    avgavgrandomoutputfile << fixed;
    avgavgrandomoutputfile << popavg_speed << ", " << popavg_x <<", " << popavg_y << ", " <<  popavg_food << endl;

  }
/*

  void population::run_brownian(int generation){
    food_present = true;
    int gen_random = 1;

    avg_speed = avg_x = avg_y = avg_food = 0;
    for(int c = 0; c < pop_size; c++){
      reset_food();
      the_pop[c].reset();
      
      for(int t = 0; t < time_steps; t++){
         step_creature(c, gen_random);
         x_values[t] = the_pop[c].getX();
         y_values[t] = the_pop[c].getY();
         speed_values[t] = the_pop[c].getSpeed();
      }
      avgbrownoutputfile << trial << ", " << generation << ", " << treatment << ", Food, Brownian, ";
      calc_stats_brownian();  // add stats to the file
      avgbrownoutputfile << the_pop[c].get_food() << "\n";
      popavg_food += the_pop[c].get_food();
       
      the_pop[c].fitness_to_gametes(&gamete_pool);
    }   // end of creatures loop
    popavg_x /= pop_size;
    popavg_y /= pop_size;
    popavg_speed /= pop_size;
    popavg_food /= pop_size;

    avgavgbrownoutputfile  << fixed;
    avgavgbrownoutputfile  << popavg_speed << ", " << popavg_x <<", " << popavg_y << ", " <<  popavg_food << endl;
//cout << popavg_speed << ", " << popavg_x <<", " << popavg_y << ", " <<  popavg_food << endl;
   // next_gen();
  }


*/
  void population::step_creature(int c, int gen_random){
         if(closest_food == -1){ // no food left
	       food_present = false;
               the_pop[c].step(0,0,&gamete_pool, gen_random);
	       food_present = true;  // for the next time
         }
         else{
            if (food_list.size() > 0) {
                if (food_list[closest_food] != NULL) {
                    if(the_pop[c].step(food_list[closest_food]->x,food_list[closest_food]->y,&gamete_pool, gen_random)){
                        //std::cout << "AHHH " << std::endl;
                        delete food_list[closest_food];
                        food_list[closest_food] = NULL;
                        //std::cout << "AHHH AHHH" << std::endl;
                        food_list.erase(food_list.begin()+closest_food);
	                }
                } else {
                    cout << closest_food << "Closest food " << endl;
                    cout << food_list.size() << "Food count " << endl;
                }
            }
         }
     
  }

  void population::next_gen(){
     creature temp[pop_size];
     int p1,p2;
     int avg_gametes=0;
     chromosome *tempc;
     if(gamete_pool.size() == 0){
        cout << "No gametes" << endl;
        for(int i = 0; i < 2*pop_size; i++){
             tempc = new chromosome();
	     gamete_pool.push_back(tempc);
        }
     }
     while(gamete_pool.size() < 2*pop_size){ // fill gamete pool if necessary
	tempc = new chromosome();
	tempc->copy(*gamete_pool[random() % gamete_pool.size()]);
	gamete_pool.push_back(tempc);
     }

     for(int i = 0; i < pop_size; i++){
        avg_gametes+= the_pop[i].get_num_gametes();
     }
//     cout << "avg: " << avg_gametes << " " << gamete_pool.size() << endl;
     std::random_shuffle(gamete_pool.begin(),gamete_pool.end());
     for(int i = 0; i < pop_size; i++){
         p1 = gamete_pool.size()-1;  // last
         p2 = gamete_pool.size()-2;  // second to last
         temp[i].create(*gamete_pool[p1],*gamete_pool[p2]);
         temp[i].mutate();
         gamete_pool.pop_back();    
         gamete_pool.pop_back();    
     }
     for(int i = 0; i < pop_size; i++){
         the_pop[i].copy(temp[i]);
         the_pop[i].reset();
     }

     for (int i = 0; i < gamete_pool.size(); i++) {
         //std::cout << "endl " << std::endl;
         delete gamete_pool[i];
         gamete_pool[i] = NULL;
         //std::cout << "endl 1" << std::endl;
     }

     gamete_pool.clear();

  } 

  
  void population::collectdata(){
    string filename;
    ofstream outfile;
    food_present = false;
    for(int i = 0; i < 1; i++){
       filename = "NoFood_";
      // filename += time(NULL);
       filename += to_string(trial);
       filename += to_string(i);
       filename += ".txt";
//       cout << filename << endl;
       outfile.open(filename.c_str());

       for(int t = 0; t < time_steps; t++){
         outfile << t <<  ", " <<  the_pop[i].getX() << ", " << the_pop[i].getY() << "\n";
         step_creature(i, gen_random);
       }
       outfile << endl;
       outfile.close();
    }

    food_present = true;
    gen_random = true;
    for(int i = 0; i < 1; i++){
       filename = "Random_";
      // filename += time(NULL);
       filename += to_string(trial);
       filename += to_string(i);
       filename += ".txt";
//       cout << filename << endl;
       outfile.open(filename.c_str());

       for(int t = 0; t < time_steps; t++){
         outfile << t <<  ", " <<  the_pop[i].getX() << ", " << the_pop[i].getY() << "\n";
         step_creature(i, gen_random);
       }
       outfile << endl;
       outfile.close();
    }


// collect data with food


// collect data with food
    food_present = true;
    gen_random = false;
    for(int i = 0; i < 1; i++){
       filename = "Food_";
       reset_food();
       the_pop[i].reset();
      // filename += time(NULL);
       filename += to_string(trial);
       filename += to_string(i);
       filename += ".txt";
//       cout << filename << endl;
       outfile.open(filename.c_str());

       for(int t = 0; t < time_steps; t++){
         outfile << t <<  ", " <<  the_pop[i].getX() << ", " << the_pop[i].getY() << "\n";
         step_creature(i, gen_random);
       }
       outfile << endl;
       outfile.close();
    }
  }
 
  string to_string(int i){
      string answer = "";
      answer += char(48+i/1000);
      i %= 1000;
      answer += char(48+i/100);
      i %= 100;
      answer += char(48+i/10);
      i %= 10;
      answer += char(48+i);
      return answer;
  }

