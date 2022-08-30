#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char g_alphabet[] = {"EP%QRdef&0123TU?45689ghijklmn-opqrstFG7HIJabcK.LMNOu+CDSvw=xyzABVWXYZ:/"};
const int g_alphabet_len = strlen(g_alphabet);
void EnOrDecode(char *text, char *key, int mode){
  int text_len = strlen(text);
  int key_len = strlen(key);
  int value;
  int j=0;
  int key_value[key_len];
  for(int i=0; i<key_len; i++){
    key_value[i] = (strchr(g_alphabet, key[i])-g_alphabet) * mode; 
  }
  printf("result:\033[0;32m");  //set result to green
  for(int i=0; i<text_len; i++){
    value = (((strchr(g_alphabet, text[i]) - g_alphabet) + key_value[j]) + g_alphabet_len) % g_alphabet_len; //((text_value)+key_value) % alphabet_len
    if(value<0){
      printf("\033[0m\ntext[%d]:(%c)\n", i, text[i]);
      printf("value:%d < 0", value);
      exit(1);
    }
    printf("%c", g_alphabet[value]);
    if(j == key_len-1) j = 0;
    else j ++;
  }
  printf("\033[0m\n");  //set color back to default
}
int main(){
  char text[4096];
  int mode;
  char key[4096];

  printf("Would you like to encode or decode [e/d]? ");
    scanf("%c", &mode); 
  while(mode != 'e' && mode != 'd'){
    getchar(); //skip new_line
    printf("Please input 'e' for encode or 'd' for decode\n");
    printf("Would you like to encode or decode [e/d]? ");
    scanf("%c", &mode); 
  }

  printf("Please input key, consisting of [A-Za-z0-9/:%%.-+=]: ");
  scanf("%s", key);
  for(int i=0; i<strlen(key); i++){
    if(!strchr(g_alphabet, key[i])){
      printf("key contain '%c', invalid, byebye!\n", key[i]);   
      exit(1);
    }
  }
  getchar(); //skip new_line

  printf("Please input text(only one line is allowed):");
  while(fgets(text, 4096, stdin) != NULL){
    if(text[strlen(text)-1] == '\n') text[strlen(text)-1] = '\0'; //remove new line

    if(mode == 'e'){
      EnOrDecode(text, key, 1);
    }
    else{
      EnOrDecode(text, key, -1);
    }
    printf("You can input next text: ");
  }

  return 0;
}
