#ifndef SET_H
#define SET_H
#include <iostream>
using namespace std;
#include <cstdlib>   // Provides size_t
    template <class Item>
    class set
    {
    public:
        // TYPEDEFS
        typedef Item value_type;
        // CONSTRUCTORS and DESTRUCTOR
        set( ){
          data_count = 0;
          child_count = 0;
          for(int i = 0; i < MAXIMUM+2; i++){
            subset[i] = NULL;
          }
        }
        set(const set& source);
        ~set( ) { clear( ); }
        // // MODIFICATION MEMBER FUNCTIONS
        void operator =(const set& source);
        void clear( );
        bool insert(const Item& entry);
        std::size_t erase(const Item& target);
        // // CONSTANT MEMBER FUNCTIONS
        std::size_t count(const Item& target) const;

        bool empty( ) const { return (data_count == 0); }
        // // SUGGESTED FUNCTION FOR DEBUGGING
        void readArr(){
          for(int i = 0; i <data_count; i++){
            cout << data[i]<< ", ";
          }
            cout <<endl;
            cout << "DATA COUNT: " << data_count << endl;
            cout << "CHILD COUNT: " << child_count<<endl;
          for(int i = 0; i < MAXIMUM + 1; i++){
                if(subset[i] != NULL){
                  cout << "SUBSET[" << i << "]" <<endl;
                  subset[i]->readArr();
                }
          }
        }
        bool inArr(const Item& target){
          for(int i = 0; i < data_count; i++){
            if(data[i]==target){
              return true;
            }
          }
          return false;
        }
        Item predecessor(const Item& entry);
    private:

      static const std::size_t MINIMUM = 1;
      static const std::size_t MAXIMUM = 2 * MINIMUM;
      Item data[MAXIMUM+1];
      std::size_t data_count;
      std::size_t child_count;
      set *subset[MAXIMUM+2];
        bool is_leaf( ) const { return (child_count == 0); }
        bool loose_insert(const Item& entry);
        bool loose_erase(const Item& target);
        void fix_excess(std::size_t i);
        void fix_shortage(std::size_t i);
        void remove_biggest(Item& removed_entry);
        bool is_leaf(){
          int count=0;
          for(int i = 0; i < MAXIMUM+2; i++){
            if(subset[i]!=NULL){
              count++;
            }
            }
            if(count ==0){
              return true;
            }
            else{
              return false;
            }
        }

      };

#include "set.cpp"
#endif
