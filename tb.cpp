#include <tb.hpp>

void tb::source(){
    // Create the input signal to be sent to fir
    // Reset (reset and 0 input)
    inp.write(0);
    rst.write(1);
    wait();

    // Next clock cycle stop writing reset
    rst.write(0);
    wait();

    // Define a temp 
    sc_int<16> tmp;
    for(int i = 0; i < 64; i++){
        if(i > 23 && i < 29){
            tmp = 256;
        }else{
            tmp = 0;
        }
        imp.write(tmp);
        wait();
    }
}

void tb::sink(){
    sc_int<16> indata;
    for(int i = 0; i < 64; i++){
        indata = outp.read();
        wait();
        cout << i << " \t: " << indata.to_int() << endl;
    }
    sc_stop();
}