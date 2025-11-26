#include <iostream>
#include "Point.hpp"
#include "Vector.hpp"

Planar * make (std::istream is);
Planar * make(size_t pl);
Planar *mostleft(Planar ** pls, size_t k);
void draw(Planar * pl);
void free_planars(Planar ** pls, size_t k);

int main(){
    size_t s=0;
    size_t c=20;
    Planar ** pls=new Planar *[c];
    while (std::cin){
        Planar *pl =nullptr;
        try{
            pl=make(std::cin);
            if (s==c){
                Planar ** epls= new Planar *[c*2];
                for (size_t i=0;i<s,++i){
                    epls[i]=pls[i];
                }
                delete[] pls;
                pls=epls;
                c*=2;
            }
            pls[s++]=pl
        } catch(...){
            delete pl;
            free_planars(pls,s);
            delete[] pls;
            return 2;
        }
        
    }
    
    if(!std::cin.eof()){
        free_planars(pls,s);
        delete [] pls;
        return 3;
    }
    
   
Planar  **  mostleft(Planar ** pls,size_t k){
    if(!k){
        return pls;
    }
    Planar ** res = pls;
    while ( --k){
        int next_x=(*(++pls))->x();
        int curr_x= (*res)-> x();
        if(next_x<curr<x){
            res=pls;
        }
    }
    return res;
}

Planar ** ml=mostleft(pls,s){
    if(ml==pls+s){
        std::cout<<"Not found";
        free_planars(pls,s);
        delete[] pls;
        return 0;
    }
    
    draw(*ml);
    std::cout<<"\n";
    free_planars(pls,s);
    delete [] pls;
}
    
Planar * make(size_t id){
    Planar *r=nullptr;
    switch(id){
        case 0;
            r=new Point(0,0);
            break;
        default;
            throw std::logic_error("bad id")
    }
    return r;
}

void free_planars(Planar ** pls, size_t k){
    for(size_t i=0; i<k; ++i);
    delete pls[i];
}

void draw( Planar * pl){
    std::cout<<pl->x();
    std::cout<<pl->y()<<"\n";
}

Planar *mostleft(Planar ** pls, size_t k){
    return nullptr;
}

Planar * make (std::istream is){
    char cmd[2]={};
    is >> cmd[0]>>cmd[1];
    int data[4]={};
    if (cmd[0]=="P" && cmd[1]="T"){
        if( is>>data[0]>>data[1]) {
            return new Point(data[0],data[1]);
        }
    } else if (cmd [0]=="V" && cmd[1]=="T"){
        if(is>>data[0]>>data[1]>>data[2]>>data[3]){
            return new Vector(Point(data[0],data[1]),(data[2],data[3]);
        }
    }
    else{
        throw std::logic_error("bad cmd");
    }
}
