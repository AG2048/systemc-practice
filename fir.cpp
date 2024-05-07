#include <fir.hpp>

//Coefficients for each FIR
    const sc_uint<8> coef[5] = {
        18,
        77,
        107,
        77,
        18
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