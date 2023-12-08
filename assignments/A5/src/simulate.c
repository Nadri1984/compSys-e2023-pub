#include "read_exec.h"
#include "assembly.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include<stdio.h> 


#define OPCODE_MASK 0x7f;// det reprentier af 0000 0000 0000 0111 1111
#define OPCODE_TO_LUI 0x37
#define MASK_TO_AUIPC 0x17
#define mask_to_JAL 0x6f


long int simulate(struct memory *mem, struct assembly *as, int start_addr, FILE *log_file) {



    int pc= start_addr;
    int register_arr[32];
    //int get_instr = memory_rd_w(mem, start_addr);//hente inst fra mem
   
    while(1){
        
        uint32_t instr = memory_rd_w(mem, pc); //vi henter instr fra hukamelsen
        uint32_t opcode = instr & OPCODE_MASK; // isolere første 7 

        // huske at spørger om func7 og U_typpen

        
        int rd_dest= (instr >> 7) & 0x1f;// >> 7 og & med 00011111
        int funct3 =(instr >>12 & 0x7); //>> 12 og & med 0111

        int rs1_sur =((instr >> 15)& 0x1f);
        int rs2_sur= ((instr >> 20)& 0x1f);
        int funct7=( (instr >> 25) & 0x3f);//111111


        switch (opcode) {
        //R_typen
        case 0x3:
       
        int func3 =((instr >>12) & 7);// >> 12 og & med 0111
        int func7=( (instr >> 25) & 7);// >> 25 og & med 0111

        //I_type
        int imd_I=((instr >>20) &  0x1f);// >> 20 og & med 00011111
        int rgister_arr_rs1  =memory_rd_h(mem, register_arr[rs1_sur]+imd_I);

        //s-typen  
        int imd_nul_fir=((instr >> 7)& 0x1f);// >> 7 og & 00011111
        int imd_fem_elev= ((instr  >> 25)  << 5 ); //>> 25 og << 5 
        int plus_null_eel= (imd_nul_fir + imd_fem_elev);


        //B_typpen
        int temp_et =(((instr >> 7) & 1)<< 11);
        int temp_to=(((instr >> 8) & 0xf)<< 1);
        int temp_tre =((instr >> 25) & 0x3f);
        int temp_fire = (((instr >>31 )<< 12 ));// eller 11
        int imd_b= (temp_et+ temp_to + temp_tre + temp_fire); 


        //U_type
        int imd_u =((instr >> 21)& 0xf);

        //J_type
        int nul_fire= (((instr >> 21) & 0xf) <<1);//
        int fem_ti =(((instr >>25) & 0x3f) << 4);
        int ti_tal = ((instr >> 20) << 11);
        int tal_net =((instr >> 12) & 0xff) <<12;
        int tov_tra= ((instr >>31 ) << 20);
        int imd_j= (nul_fire + fem_ti +ti_tal +tal_net + tov_tra);

        
            //under case
            // switch (funct3){
                
            //     case 0x0:
                
            //     int register_arr_rs1= memory_rd_b(mem, register_arr[rs1_sur]+imd_I);
            //     break;
            //     case 0x1:
            //         /// her skal man lave ene 
            //         int register_arr_rs1  =memory_rd_h(mem, register_arr[rs1_sur]+imd_I);//ofset
            //     break;
            //         int register_arr_rs1 = memory_rd_w(mem, register_arr[rs1_sur]+imd_I);
                
            //     case 0x2:

            //     break;

            case OPCODE_TO_LUI:
                register_arr[rd_dest] =((instr >> 12) <<12);
                break;

            case MASK_TO_AUIPC:
                register_arr[rd_dest] = pc | ((instr >> 12) <<12);
                break;

            
            // case mask_to_JAL:
            //     register_arr[rd_dest] = pc + 4);



        
        default:
                //håner 

            break;
            }
        }



 }


