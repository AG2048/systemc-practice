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

// FIR Main thread (fir:: scopes fir_main under fir module)
void fir::fir_main(void){
    // This code continuously runs your multi-clock-cycle code, unless reset signal is received then it breaks out the while loop

    // RESET behaviour (local var or outputs)
    outp.write(0); // reset output

    wait(); // automatically waits 1 cycle

    while(true){
        // Read inputs
        for(int i = 4; i > 0; i--){
            taps[i] = taps[i-1]; // shift data
        }
        taps[0] = input.read(); // load in new data
        // Algo
        sc_int<16> val;
        for(int i = 0; i < 5; i++){
            val += coef[i] * taps[i];
        }
        // Write
        outp.write(val);
        // Wait for clock boundary
        wait();
    }
}