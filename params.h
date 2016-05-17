/* Genome output
 * each fish output
 * processing
 * 50 rep
 */


const int treatment = 1;
bool predator = true;
double surviveAtTop = 0.85;
double step = 20;
//sigmoidal variables
double  i = 0;
double e = 2.7183;
double ro =.02;
const int corn = 250;
//const int x= 1;
const int  a =0;
bool chance(double rate) {
  if ((double) rand() / RAND_MAX < rate) {
    return true;
  }
  return false;
}

const int width = 1000;
const int height = 500;
const int input_size = 3;
const int output_size = 3;
const int time_steps = 3000;
const int max_generations = 100;
//const int max_trials = 4; // 20;  trials are handled by qsub
const int food_amount = 100;
int trial;
const int hidden_size = 5;

//const int num_weights = input_size * hidden_size + hidden_size*output_size;
const int num_weights = input_size * output_size;

const int sensing_range = 125;

const int food_range = 8;
int num_gametes_per_food = 2;

const int pop_size = 1000;


bool dataCollection = false;
bool useFitness = false;
bool food_present = true;

double mutation_rate = .01;  // percent
double mutation_size = 2;  // range is -0.5*mutation_size to 0.5*mutation_size
double mean = 0; //Mean for normal distribution
double stddev = 1; //Standar devation for normal distribution

bool normal_dist = true;

boost::mt19937 rng(static_cast<unsigned int>(time(NULL)));
/*According to the docs, mean and std dev distr(mean, stddev)*/
boost::normal_distribution<> distribution(mean, stddev);
boost::variate_generator< boost::mt19937, boost::normal_distribution<> > dist(rng, distribution);



