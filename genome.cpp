
class chromosome{
  private:
     double weights[num_weights];
  public:  
     chromosome();
//     chromosome(const chromosome&);
     void mutate();
     void copy(chromosome);
     double get_weight(int);
     void print();
     void initialize();
};
  
  chromosome::chromosome(){
    for(int i =0; i < num_weights; i++){
      weights[i] = 0;  // random(-0.1,0.1);
    }
  } 

  void chromosome::initialize(){
    for(int i =0; i < num_weights; i++){
          weights[i] += 2.0*( ((rand() % 100) / 100.0) - 0.5) ;
    }
//    weights[1] = 100;
//    weights[11] = 100;
  }
 

  void chromosome::print(){
    for(int i =0; i < 10; i++){ //num_weights; i++){
       cout << weights[i] << " ";
    }
    cout << "\n";
  }
  
  void chromosome::copy(chromosome source){
    for(int i =0; i < num_weights; i++){
      weights[i] = source.weights[i];
    }
  }
    
  double chromosome::get_weight(int i){
    return(weights[i]);
  }   

  void chromosome::mutate() {
        if (normal_dist) {
            for(int i =0; i < num_weights; i++){
                if((rand()%100)< mutation_rate) {
                    /*dist is from the boost normal dist*/
                    /*I tested it dist(), the probs are as expected and it seems to be working correctly*/
                    weights[i] += dist();
                }
            }
        } else {
            for(int i =0; i < num_weights; i++){
                if((rand()%100) < mutation_rate){
                    weights[i] += mutation_size*( ((rand() % 100) / 100.0) - 0.5) ;
                }
            }
        }

  }

class genome{
  private:
    chromosome maternal;
    chromosome paternal;
  public:
    genome();
    genome(chromosome,chromosome);
    void mutate();
    void print();
    chromosome getGamete();
    chromosome getMaternal();
    chromosome getPaternal();
    double getWeight(int);
    void create(chromosome,chromosome);
};

  genome::genome(){
    maternal.initialize();
    paternal.initialize();
  }

  genome::genome(chromosome m, chromosome p){
      maternal.copy(m);
      paternal.copy(p);
  }
     
  void genome::create(chromosome m, chromosome p){
      maternal.copy(m);
      paternal.copy(p);
  }
    
  void genome::mutate(){
    maternal.mutate();
    paternal.mutate();
  }

  void genome::print(){
    maternal.print();
    paternal.print();
  }
  
  chromosome genome::getGamete(){
    if(rand()%100 < 50){
      return maternal;
    }
    else{
      return paternal;
    }
  }
  
  chromosome genome::getMaternal(){
    return maternal;
  }
  
  chromosome genome::getPaternal(){
    return paternal;
  }

  
  double genome::getWeight(int i){
    return((maternal.get_weight(i)+paternal.get_weight(i)));
  }
  
