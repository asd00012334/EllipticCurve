#ifndef __KARATSUBA_HPP__
#define __KARATSUBA_HPP__

#include<vector>

namespace ECC{

using namespace std;

static int const threshold = 16;

template<typename Ring>
void convKernel(Ring const* type,
                vector<typename Ring::Element>& l,
                vector<typename Ring::Element>& r,
                vector<typename Ring::Element>& result){
    using RingElement = typename Ring::Element;
    /// Assume l.size() == r.size() == pow(2,k)
    /// Assume left as low bit and right as high bit
    int size=l.size();
    result=vector<RingElement>(size*2,type->zero());
    if(size<=threshold){
        for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            result[i+j]+=l[i]*r[j];
        return;
    }
    int hSize=size/2;
    vector<RingElement> ll(hSize), rl(hSize);
    vector<RingElement> lr(hSize), rr(hSize);
    vector<RingElement> lmix(hSize), rmix(hSize);
    for(int cnt=0;cnt<size;cnt++){
        if(cnt<hSize){
            ll[cnt]=l[cnt];
            rl[cnt]=r[cnt];
            lmix[cnt]=l[cnt];
            rmix[cnt]=r[cnt];
        } else{
            lr[cnt-hSize]=l[cnt];
            rr[cnt-hSize]=r[cnt];
            lmix[cnt-hSize]+=l[cnt];
            rmix[cnt-hSize]+=r[cnt];
        }
    }
    vector<RingElement> leftResult, mixResult, rightResult;
    convKernel(ll,rl,leftResult);
    convKernel(lr,rr,rightResult);
    convKernel(lmix,rmix,mixResult);

    for(int cnt=0;cnt<size;cnt++){
        result[cnt+hSize*2]+=rightResult[cnt];
        result[cnt+hSize]+=mixResult[cnt]-rightResult[cnt]-leftResult[cnt];
        result[cnt]+=leftResult[cnt];
    }
}

template<typename Ring>
void conv(Ring const* type,
          vector<typename Ring::Element>& l,
          vector<typename Ring::Element>& r,
          vector<typename Ring::Element>& result){
    int n=max(l.size(),r.size());
    n=pow(2,ceil(log2(n)));
    l.resize(n,type->zero());
    r.resize(n,type->zero());
    convKernel(l,r,result);
}

}
#endif // __KARATSUBA_HPP__
