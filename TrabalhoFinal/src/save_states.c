#include "save_states.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>

int savefile_savesamnt(char* savefile_name){
    FILE* savefile;
    if(!(savefile = fopen(savefile_name, "rb"))){
        printf("Erro ao tentar abrir %s\n", savefile_name);
        return -1;
    }

    int size;

    fseek(savefile, 0, SEEK_END);
    size = ftell(savefile) / sizeof(save_state);
    fclose(savefile);

    return size;
}

int load_save_file(char* savefile_name, pSave_state saves_v){
    int save_amnt = savefile_savesamnt(savefile_name);

    FILE* savefile;
    if(!(savefile = fopen(savefile_name, "rb")) || (save_amnt < 0)){
        return -1;
    }

    if(save_amnt){
        fread(saves_v, sizeof(save_state), save_amnt, savefile);
    }

    fclose(savefile);
    return save_amnt;

}

int write_save_to_file(char* savefile_name, pSave_state save_to_write, int pos){
    int append = (saves_loaded > 0 || pos > saves_loaded);

    FILE* savefile;
    if(!(savefile = fopen(savefile_name, append? "ab" : "r+b"))){
        return 0;
    }

    if(!append){
        fseek(savefile, pos * sizeof(save_state), SEEK_SET);
    }

    fwrite(save_to_write, sizeof(save_state), 1, savefile);
    fclose(savefile);

    return 1;
}

void new_save_state(pSave_state save, char* p_name){
    strcpy(save->player_name, p_name);
    save->save_id = saves_loaded + 1;
    save->cur_level = 1;
    save->lives = 3;
    save->points = 0;
}

void delete_save(char* savefile_name, int pos){
    FILE* savefile;
    if(!(savefile = fopen(savefile_name, "wb"))){
        return;
    }    
    int i;
    save_state temp[MAX_SAVES];
    for(i = 0; i < pos; i++){
        temp[i] = all_saves[i];
        temp[i].save_id = i + 1;
    }
    for(i = pos + 1; i < MAX_SAVES; i++){
        temp[i - 1] = all_saves[i];
        temp[i - 1].save_id = i;
    }

    fwrite(temp, sizeof(save_state), saves_loaded - 1, savefile);
    fclose(savefile);

}