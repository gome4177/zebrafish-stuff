class food{
   public:
     float x;
     float y;
     food();
     ~food();
     void anywhere();
     void top();
     void bottom();
     void falling();
     void move();
     int fall();
};

food::~food() {

}

food::food(){
   x = random()%width;
   y = random() % height;
}

void food::anywhere(){
   x = random()%width;
   y = random() % height;
}

void food::top(){
   x = random()%width;
   y = random() % 50;
}

void food::bottom(){
   x = random()%width;
   y = height - (random() % 50);
}

void food::falling(){
   x = random()%width;
   y = 0;  // starts at top then falls
}
void food::move(){
   x += (random()%((food_range-1)*2+1))-(food_range-1);
   y += (random()%((food_range-1)*2+1))-(food_range-1);
   //std::cout << (random()%((food_range-1)*2+1))-(food_range-1) << std::endl;
   //x += (random()%(16)-8);
   //y += (random()%(16)-8);

   if(y > height){
       y = height;
   } else if (y < 0) {
       y = 0;
   }

   if (x > width) {
       x = width;
   } else if (x < 0) {
       x = 0;
   }

}

int food::fall(){
   y = y + 2;
   if(y > height){
      return 0;
   }
   return 1;
}

