#include <iostream>
#include <cstdlib>
using namespace std;

template <class Item>
bool set<Item>:: loose_insert(const Item& entry){
  if(count(entry)>0){
    return false;
  }
  int location =0;
  for(int i = 0; i < data_count; i++){
    if(entry>data[i]){
      location++;
    }
  }
  //DATA MUST BE PLACED HERE NO MATTER WHAT THIS IS A BASE CASE
  if(is_leaf()){
          for(int i = data_count; i > location; i--){
            data[i]= data[i-1];
          }
          data[location] = entry;
          data_count++;
          return true;
  }
  else{
    subset[location] -> loose_insert(entry);
  }
  if(subset[location]->data_count > MAXIMUM){
    fix_excess(location);
  }
  return true;
}

template <class Item>
bool set<Item>::insert(const Item& entry){
        if(loose_insert(entry) == false){
          return false;
        }
    //VERY TOP NODE HAS A VIOLATION AND NEEDS TO SPLIT HAVING THE ROOT ONLY HAVE 1 VALUE
        if(data_count>MAXIMUM){
          //IF IT IS SPLTING OFF FROM A ONE LEVEL TO A TWO LEVEL
          if(is_leaf()){
          subset[0] = new set;
          for(int i = 0; i < MAXIMUM/2; i++){
            subset[0]->insert(data[i]);
          }

        subset[1] = new set;
        for(int i = MAXIMUM; i > MAXIMUM/2; i--){
          subset[1]->insert(data[i]);
        }
        child_count = 2;
        data[0]= data[MINIMUM];
        data_count = 1;
      }
      else{
        set* temp[MAXIMUM+2];
        for (int i = 0; i < MAXIMUM +2; i++){
          temp[i] = subset[i];
        }
        subset[0] = new set;
        for(int i = 0; i < MAXIMUM/2; i++){
          subset[0]->insert(data[i]);
        }
        for(int i = 0; i <= MINIMUM; i++){
          subset[0]->subset[i] = temp[i];
        }
        subset[0]->child_count = MINIMUM+1;
      subset[1] = new set;
      for(int i = MAXIMUM; i > MINIMUM; i--){
        subset[1]->insert(data[i]);
      }
      int j = 0;
      for(int i = MINIMUM+1; i < MAXIMUM+2; i++){
        subset[1]->subset[j] = temp[i];
        j++;
      }
      subset[1]->child_count = MINIMUM+1;
      child_count = 2;
      for(int i = 2; i < MAXIMUM+2; i++){
        subset[i]= NULL;
      }
      data[0]= data[MINIMUM];
      data_count = 1;
      }
    }
        return true;
}

template <class Item>
void set<Item>:: fix_excess(std::size_t i){
      //i is the location of the subset
      for(int j = data_count; j > i; j--){
        data[j]= data[j-1];
      }
      data[i] = subset[i]->data[MINIMUM];
      data_count++;
  //SHIFTING CHILDREN IF THE VIOLATION IS IN THE RIGHT MOST CHILD
    if(i == child_count-1){
      if(subset[i]->is_leaf()){
          subset[child_count] = new set;

          for(int k = MINIMUM+1; k < MAXIMUM+1; k++){
            subset[child_count]->insert(subset[i]->data[k]);
          }
          child_count ++;
          subset[i]->data_count = MINIMUM;
        }
      else{
        set* temp[MAXIMUM+2];
        for (int j = 0; j < MAXIMUM +2; j++){
          temp[j] = subset[i]->subset[j];
        }
        subset[child_count] = new set;

        for(int k = MINIMUM+1; k < MAXIMUM+1; k++){
          subset[child_count]->insert(subset[i]->data[k]);
        }
        int q = 0;
        for(int p = MINIMUM+1; p <MAXIMUM+2; p++){
          subset[child_count]->subset[q] = subset[i]->subset[p];
          q++;
        }
        subset[child_count]->child_count = MINIMUM+1;
        child_count ++;
        subset[i]->data_count = MINIMUM;
        for(int l = MINIMUM+1; l < MAXIMUM+2; l++){
          subset[i]->subset[l] =NULL;
        }
        subset[i]->child_count = MINIMUM+1;
      }
    }
    else{
          if(subset[i]->is_leaf()){
              for(int k = child_count; k>i; k--){
                subset[k] = subset[k-1];
              }
              child_count++;
              subset[i] = new set;
              for(int k = 0; k<MINIMUM; k++){
                subset[i]->insert(subset[i+1]->data[k]);
              }
              int j = 0;
              for(int k = MINIMUM+1; k<=MAXIMUM; k++){
                subset[i+1]->data[j] = subset[i+1]->data[k];
                j++;
              }
              subset[i+1]->data_count = MINIMUM;
        }
        else{
              set* temp[MAXIMUM+2];
              for (int j = 0; j < MAXIMUM +2; j++){
                temp[j] = subset[i]->subset[j];
              }

              for(int k = child_count; k>i+1; k--){
                subset[k] = subset[k-1];
              }
              child_count++;
              subset[i+1] = new set;
              for(int k = MINIMUM+1; k<MAXIMUM+1; k++){
                subset[i+1]->insert(subset[i]->data[k]);
              }

              int q = 0;
              for(int p = MINIMUM+1; p <MAXIMUM+2; p++){
                subset[i+1]->subset[q] = subset[i]->subset[p];
                q++;
              }
              subset[i+1]->child_count = MINIMUM+1;
              subset[i]->data_count = MINIMUM;
              for(int l = MINIMUM+1; l < MAXIMUM+2; l++){
                subset[i]->subset[l] =NULL;
              }
              subset[i]->child_count = MINIMUM+1;
        }
    }


}

template <class Item>
void set<Item>::clear( ){
  for(int i = 0; i < MAXIMUM; i++){
    if(subset[i]!=NULL){
      delete subset[i];
      subset[i]=NULL;
    }
  }
  data_count = 0;
}

template <class Item>
std::size_t set<Item>:: count(const Item& target) const{

  size_t hit = 0;
  if(data_count == 0){
    return hit;
  }
  //CHECKING TO SEE IF IT IS IN THE CURRENT DATA
  for(int i = 0; i < data_count; i ++){
    if(data[i] == target){hit++;}
  }
  if(hit > 0){return hit;}
  else{
    int location = 0;
    for(int i = 0; i < data_count; i++){
      if(target>data[i]){
        location++;
      }
    }
    if(is_leaf()){
      return hit;
    }
    else{
    hit = subset[location]->count(target);
  }
  }
  return hit;
}

template <class Item>
bool set<Item>::loose_erase(const Item& target){
  if(count(target)==0){
    return false;
  }

  int location =0;
  for(int i = 0; i < data_count; i++){
    if(target>data[i]){
      location++;
    }
  }
  bool hit = false;
  for(int i = 0; i < data_count; i++){
    if(target == data[i]){
      hit = true;
    }
  }
  //DATA MUST BE PLACED HERE NO MATTER WHAT THIS IS A BASE CASE
      //ADJUST CHILDREN JUST IN CASE NOT A LEAF
  if(hit == true){
    //AM I A LEAF?
    if(is_leaf()==0){
      Item temp = predecessor(target);
      data[location] = temp;
      subset[location]->loose_erase(temp);
    }
    //Last element of the array
    else{
    if(location == data_count-1){ data_count --;}
    //INSIDE THE ARRAY OR BEGINNING
    else{
      for(int i = location; i < data_count; i++){
        data[i] = data[i+1];
      }
      data_count --;
    }
    return true;
  }
  }
  else{
    subset[location]->loose_erase(target);
  }
  if(subset[location]->data_count < MINIMUM){
    fix_shortage(location);
  }
  return true;
}

template <class Item>
std::size_t set<Item>::erase(const Item& target){
  if(loose_erase(target)==false){
    return -1;
  }
  if(data_count == 0 && child_count ==0){
    return 1;
  }
  else if(data_count == 0){
    set* temp[MAXIMUM+2];
    for (int j = 0; j < MAXIMUM +2; j++){
      temp[j] = subset[0]->subset[j];
    }
    for(int i = 0; i < subset[0]->data_count; i++){
      data[i]= subset[0]->data[i];
    }
    data_count = subset[0]->data_count;
    child_count = subset[0]->child_count;
    for(int i = 0; i < MAXIMUM +2; i++){
      subset[i] = temp[i];
    }

  }
  return -2;
}

template <class Item>
  void set<Item>::fix_shortage(std::size_t i){
    //RIGHT MOST SIBLING
                  if(i == child_count-1){

        //LEFT SIBLING IS ABLE TO GIVE IT UP
                      if(subset[i-1]->data_count != MINIMUM){
                          if(subset[i]->is_leaf()==0){
                            for(int j = subset[i]->child_count; j >0; j--){
                              subset[i]->subset[j]=subset[i]->subset[j-1];

                            }

                            subset[i]->subset[0]=subset[i-1]->subset[subset[i-1]->child_count-1];

                            subset[i]->child_count++;
                            subset[i-1]->subset[subset[i-1]->child_count-1] = NULL;
                            subset[i-1]->child_count--;
                          }
                          //CHECK FOR NON LEAVES
                      //SHIFTS THE NODES TO THE RIGHT SO THAT THE VALUE FROM THE PARENT CAN BE PASSED IN
                      for(int k = subset[i]->data_count; k > 0; k--){
                        subset[i]->data[k] = subset[i]->data[k-1];
                      }
                      subset[i]->data[0] = data[i-1];
                      subset[i]->data_count ++;
                      // PARENT TAKES VALUE FROM CHILD AND DELETE THE GIVING CHILD'S DATA POINT
                        int borrowIndex = subset[i-1]->data_count -1;
                        data[i -1] = subset[i-1]->data[borrowIndex];
                        subset[i-1]->data_count--;
                      }
        //LEFT SIBLING IS AT MINIMUM BUT PARENT *** IS ABLE *** TO GIVE UP A VALUE
                      else{

                        if(subset[i]->is_leaf()==0){
                          int k = 0;
                          for(int j = subset[i-1]->child_count; j < subset[i-1]->child_count+subset[i]->child_count; j++){
                            subset[i-1]->subset[j] = subset[i]->subset[k];
                            k++;
                          }
                          subset[i-1]->child_count += subset[i]->child_count;
                        }
                        //PUTS THE PARENT DATA VALUE IN THE LEFT CHILD'S ARRAY
                        subset[i-1]->data[subset[i-1]->data_count] = data[i-1];
                        subset[i-1]->data_count ++;
                        //ADDS THE TARGET'S ARRAY TO THE LEFT CHILD'S ARRAY
                        //(NOW THE LEFT ARRAY, PARENT VALUE AND RIGHT ARRAY ALL ALL IN THE LEFT ARRAY)
                        int j = 0;
                        for(int k = subset[i-1]->data_count; k < subset[i-1]->data_count + MINIMUM; k++){
                          subset[i-1]->data[k] = subset[i]->data[j];
                          j++;
                        }
                        subset[i-1]->data_count+= MINIMUM-1;

                        //UPDATING THE DATA COUNT FOR THE CURRENT ROOT SINCE THE PARENT GAVE UP A VALUE
                        data_count--;
                        //UPDATING THE CHILDREN FOR THE CURRENT ROOT
                        subset[i] = NULL;
                        child_count --;
                      }

                  }
    //LEFT MOST CHILD
                  else if (i == 0){
            //
            // //IF RIGHT SIBLING CAN GIVE UP A NODE
                        if(subset[i+1]->data_count != MINIMUM){
                          if(subset[i]->is_leaf()==0){
                            subset[i]->subset[subset[i]->child_count] = subset[i+1]->subset[0];
                            subset[i]->child_count++;
                            for(int j = 0; j < subset[i+1]->child_count-1; j++){
                              subset[i+1]->subset[j]=subset[i+1]->subset[j+1];
                            }
                            subset[i+1]->subset[subset[i+1]->child_count-1] = NULL;
                            subset[i+1]->child_count --;
                          }
                            //SHIFTS THE NODES TO THE RIGHT SO THAT THE VALUE FROM THE PARENT CAN BE PASSED IN
                            subset[i]->data[subset[i]->data_count] = data[i];
                            subset[i]->data_count++;
                            // PARENT TAKES VALUE FROM CHILD AND DELETE THE GIVING CHILDS DATA POINT
                            int borrowIndex = subset[i+1]->data_count -1;
                            data[i] = subset[i+1]->data[0];
                            for(int k = 0; k < subset[i+1]->data_count-1; k++){
                              subset[i+1]->data[k]=subset[i+1]->data[k+1];
                            }
                            subset[i+1]->data_count--;

                      }
          //RIGHT CANNOT GIVE UP BUT PARENT CAN
                    else{
                      if(subset[i]->is_leaf()==0){
                        int k = 0;
                        for(int j = subset[i]->child_count; j < subset[i]->child_count+subset[i+1]->child_count; j++){
                          subset[i]->subset[j] = subset[i+1]->subset[k];
                          k++;
                        }
                      }
                        //INSERTING THE VALUE FROM THE PARENT TO THE END OF THE ARRAY THAT THE TARGET IS IN
                        subset[i]->data[subset[i]->data_count] = data[i];
                        subset[i]->data_count ++;
                        subset[i]->child_count += subset[i+1]->child_count;
                        //ADDING THE RIGHT ARRAY TO THE ARRAY THAT THE TARGET IS IN
                        //NOW TARGET ARRAY, PARENT VALUE AND RIGHT ARRAY IS IN THE TARGET ARRAY(AKA THE LEFT MOST CHILD)
                        int j = 0;
                        for(int k = subset[i]->data_count; k < subset[i]->data_count+ MINIMUM; k++){
                          subset[i]->data[k] = subset[i+1]->data[j];
                          j++;
                        }
                        subset[i]->data_count += MINIMUM;
                        //ADJUSTING THE CURRENT ROOT TO ACCOMIDATE LOOSING A VALUE
                        for(int k = i; k < data_count-1; k++){
                          data[k] = data[k+1];
                        }
                        data_count --;
                        //ADJUSTING THE CHILDREN
                        for (int k = i+1; k < child_count-1; k++){
                          subset[k] = subset[k+1];
                        }
                        subset[child_count-1] =NULL;
                        child_count--;
                }
                }
    // //ALL INBETWEEN
                else{
        //TAKE FIRST FROM LEFT
                        if(subset[i-1]->data_count != MINIMUM){
                          if(subset[i]->is_leaf()==0){
                            for(int j = subset[i]->child_count; j >0; j--){
                              subset[i]->subset[j]=subset[i]->subset[j-1];
                            }
                            subset[i]->subset[0]=subset[i-1]->subset[subset[i-1]->child_count-1];
                            subset[i]->child_count++;
                            subset[i-1]->subset[subset[i-1]->child_count-1] = NULL;
                            subset[i-1]->child_count--;
                          }
                          for(int k = subset[i]->data_count; k > 0; k--){
                            subset[i]->data[k] = subset[i]->data[k-1];
                          }
                          subset[i]->data[0] = data[i-1];
                          subset[i]->data_count ++;
                          // PARENT TAKES VALUE FROM CHILD AND DELETE THE GIVING CHILD'S DATA POINT
                            int borrowIndex = subset[i-1]->data_count -1;
                            data[i -1] = subset[i-1]->data[borrowIndex];
                            subset[i-1]->data_count--;
                          }
        // IF LEFT IS MINIMUM TRY TO TAKE FROM RIGHT
                        else if(subset[i+1]->data_count != MINIMUM){
                          if(subset[i]->is_leaf()==0){
                            subset[i]->subset[subset[i]->child_count] = subset[i+1]->subset[0];
                            subset[i]->child_count++;
                            for(int j = 0; j < subset[i+1]->child_count-1; j++){
                              subset[i+1]->subset[j]=subset[i+1]->subset[j+1];
                            }
                            subset[i+1]->subset[subset[i+1]->child_count-1] = NULL;
                            subset[i+1]->child_count --;
                          }
                          //SHIFTS THE NODES TO THE RIGHT SO THAT THE VALUE FROM THE PARENT CAN BE PASSED IN
                          subset[i]->data[subset[i]->data_count] = data[i];
                          subset[i]->data_count++;
                          // PARENT TAKES VALUE FROM CHILD AND DELETE THE GIVING CHILDS DATA POINT
                          int borrowIndex = subset[i+1]->data_count -1;
                          data[i] = subset[i+1]->data[0];
                          for(int k = 0; k < subset[i+1]->data_count-1; k++){
                            subset[i+1]->data[k]=subset[i+1]->data[k+1];
                          }
                          subset[i+1]->data_count--;
                      }
          // //IF IT CANNOT TAKE FROM THE LEFT AND THE PARENT CAN GIVE UP ITS VALUE
                        else{
                            if(subset[i]->is_leaf()==0){
                              int k = 0;
                              for(int j = subset[i-1]->child_count; j < subset[i-1]->child_count+subset[i]->child_count; j++){
                                subset[i-1]->subset[j] = subset[i]->subset[k];
                                k++;
                              }
                              subset[i-1]->child_count ++;

                            }
                        //PUTS THE PARENT DATA VALUE IN THE LEFT CHILD'S ARRAY
                        subset[i-1]->data[subset[i-1]->data_count] = data[i-1];
                        subset[i-1]->data_count ++;
                        //ADDS THE TARGET'S ARRAY TO THE LEFT CHILD'S ARRAY
                        //(NOW THE LEFT ARRAY, PARENT VALUE AND RIGHT ARRAY ALL ALL IN THE LEFT ARRAY)
                        int j = 0;
                        for(int k = subset[i-1]->data_count; k < subset[i-1]->data_count + subset[i]->data_count; k++){
                          subset[i-1]->data[k] = subset[i]->data[j];
                          j++;
                        }
                        subset[i-1]->data_count+= subset[i]->data_count;

                        //UPDATING THE DATA COUNT FOR THE CURRENT ROOT SINCE THE PARENT GAVE UP A VALUE
                        for(int k = i-1; k < data_count-1; k++){
                          data[k] = data[k+1];
                        }
                        data_count--;
                        if(subset[i+1]->is_leaf()==0){
                          for(int m = i; m < child_count; m++){
                            subset[m]=subset[m+1];
                          }
                          subset[child_count -1] = NULL;
                        }
                        child_count --;
                    }

                }
  }


template <class Item>
Item set<Item>::predecessor(const Item& entry){
  Item pre;
  bool hit = false;
  if(is_leaf()){
    pre = data[data_count-1];
    return pre;
  }
  int location =0;
  for(int i = 0; i < data_count; i++){
    if(entry>data[i]){
      location++;
    }
  }
  for(int i = 0; i < data_count; i++){
    if(entry == data[i]){
      hit = true;
    }
  }
  if(hit == true){
    pre = subset[location]->predecessor(entry);
  }
  else{
    pre = subset[child_count -1]->predecessor(entry);
  }
  return pre;
}

template <class Item>
void set<Item>::remove_biggest(Item& removed_entry){
    if(is_leaf()){
      removed_entry = data[data_count-1];
      data_count--;
      return;
    }
    subset[child_count-1]->remove_biggest(removed_entry);
    if(subset[child_count-1]->data_count < MINIMUM){
      fix_shortage(child_count-1);
    }

}
