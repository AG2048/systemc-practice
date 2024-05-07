#include <fir.hpp>

//Coefficients for each FIR
    const sc_uint<8> coef[5] = {
        18,
        77,
        107,
        77,
        18
    };

// FIR Main thread (fir:: scopes fir_main under fir module)
void fir::fir_main(void){
    // This code continuously runs your multi-clock-cycle code, unless reset signal is received then it breaks out the while loop
    sc_int<16> taps[5];

    // RESET behaviour (local var or outputs)
    // Initialize handshake
    inp_rdy.write(0); // Initially input is not ready
    outp_vld.write(0); // Initially output is not valid
    outp.write(0); // reset output

    wait(); // automatically waits 1 cycle

    while(true){
        // Handshake: I'm ready to receive data
        inp_rdy.write(1);
        do{
            wait();
        } while(!inp_vld.read()); // Wait until data is valid - we read when its ready

        // Read inputs
        for(int i = 4; i > 0; i--){
            taps[i] = taps[i-1]; // shift data
        }
        taps[0] = inp.read(); // load in new data
        // Handshake: don't write to me now
        inp_rdy.write(0);

        // Algo
        sc_int<16> val;
        for(int i = 0; i < 5; i++){
            val += coef[i] * taps[i];
        }
        // Write
        outp.write(val);
        // Handshake: i'm now writing valid data
        outp_vld.write(1);
        do{
            wait();
        }while(!outp_rdy.read()); // wait until outp is ready - we 
        outp_vld.write(0);
        // Wait for clock boundary
        wait();
    }
}