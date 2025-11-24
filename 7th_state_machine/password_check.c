//"B,C,C,A"
int password(int A, int B, int C)   {
    static int state = 0;
    switch(state)   {
        case 0:
            if(B == 1){ state = 1;}
        return 0;
        case 1: 
            if(C == 1){ state = 2;}
            else if(A == 1){ state = 0;}
        return 0;
        case 2: 
            if(C == 1){ state = 3;}
            else if(A == 1){ state = 0;}
            else if(B == 1){ state = 0;}
        return 0;
        case 3: 
            if(A == 1){ state = 4;
            return 1;
            }
            else if(B == 1){ state = 0;}
            else if(C == 1){ state = 0;}
        return 0;
    }
}