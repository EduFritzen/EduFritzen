#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    string t;
    int Tc=0,Ts=0,Tv=0;
    int i,j=0;
    int * Ncar= new int [100], * Nspc= new int [100], * Nvog= new int [100];
    char * vet;
    for(i=0;i<4;i++){
        Ncar[i]=0;
        Nspc[i]=0;
        Nvog[i]=0;
    }
    while (getline(cin,t)){
        vet = new char[t.size()+1];
        strncpy(vet, t.c_str(), t.size());
        vet[t.size()]='\0';
        for(i=0;i<=t.size();i++){
            if(vet[i]!= '\0' && vet[i]!=' ' && vet[i]!=','&& vet[i]!='.'){
                Ncar[j]= Ncar[j] + 1;
            }  
            if(vet[i]==' '){
                Nspc[j]= Nspc[j] + 1;
            } 
            if(vet[i]=='a'||vet[i]=='e'||vet[i]=='i'||vet[i]=='o'||vet[i]=='u'||vet[i]=='A'||vet[i]=='E'||vet[i]=='I'||vet[i]=='O'||vet[i]=='U'){
                Nvog[j]= Nvog[j] + 1; 
            }        
        }     
        j++; 
        delete [] vet;  
    }
    for(i=0;i<j;i++){
        Tc= Tc + Ncar[i];
        Ts= Ts + Nspc[i];
        Tv= Tv + Nvog[i];
    }
    cout << "\n" << Tc << " " << Ts << " " << Tv;
    for(i=0;i<j;i++){
        cout << "\n" << Ncar[i] << " " << Nspc[i] << " " << Nvog[i] << "\n";
    }
    delete [] Ncar, Nspc, Nvog;
    return 0;
}
