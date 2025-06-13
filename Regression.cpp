#include "Regression.hpp"
#include "LeastSquares.hpp"
#include "Matrix.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <iostream>
#include <cctype>
struct Sample{ double f[6]; double prp; };
static std::string trim(std::string s){ size_t b=0,e=s.size(); while(b<e && std::isspace((unsigned char)s[b]))++b; while(e>b && std::isspace((unsigned char)s[e-1]))--e; return s.substr(b,e-b); }
static bool LoadDataset(const char* path,std::vector<Sample>& out){ std::ifstream fin(path); if(!fin) return false; std::string line; while(std::getline(fin,line)){ if(line.empty()) continue; std::stringstream ss(line); std::string field; std::getline(ss,field,','); std::getline(ss,field,','); Sample s{}; for(int i=0;i<6;++i){ if(!std::getline(ss,field,',')) return false; s.f[i]=std::stod(trim(field)); } if(!std::getline(ss,field,',')) return false; s.prp=std::stod(trim(field)); out.push_back(s);} return true; }
static void BuildXY(const std::vector<Sample>& data,Matrix& X,Vector& y){ int n=(int)data.size(); for(int i=1;i<=n;++i){ for(int j=0;j<6;++j) X(i,j+1)=data[i-1].f[j]; y(i)=data[i-1].prp; }}
void RunPartB(const char* csvPath){ std::vector<Sample> samples; if(!LoadDataset(csvPath,samples)){ std::cerr<<"Cannot read '"<<csvPath<<"'\n"; return; }
    std::mt19937 rng(42); std::shuffle(samples.begin(),samples.end(),rng);
    int nTot=(int)samples.size(); int nTrain=(int)(0.8*nTot+0.5); int nTest=nTot-nTrain;
    std::vector<Sample> train(samples.begin(),samples.begin()+nTrain); std::vector<Sample> test(samples.begin()+nTrain,samples.end());
    Matrix Xtr(nTrain,6), Xte(nTest,6); Vector ytr(nTrain), yte(nTest); BuildXY(train,Xtr,ytr); BuildXY(test,Xte,yte);
    Vector beta=SolveLeastSquares(Xtr,ytr);
    Vector yPred=Xte*beta; double sse=0.0; for(int i=1;i<=nTest;++i){ double d=yPred(i)-yte(i); sse+=d*d; }
    double rmse=std::sqrt(sse/nTest);
    std::cout<<"\n===== Part B results =====\n"; const char* names[6]={"MYCT","MMIN","MMAX","CACH","CHMIN","CHMAX"};
    for(int i=1;i<=6;++i) std::cout<<std::setw(6)<<names[i-1]<<" : "<<std::fixed<<std::setprecision(6)<<beta(i)<<'\n';
    std::cout<<"RMSE (test 20%) : "<<rmse<<"\n";
}