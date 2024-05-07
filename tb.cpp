#include <tb.hpp>

void tb::source(){
    // Create the input signal to be sent to fir
    // Reset (reset and 0 input)
    inp.write(0);
    rst.write(1);
    // Handshake
    inp_valid.write(0); // Data is not ready

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
        // Indicate to fir new valid data is now transmitted
        inp_vld.write(1);
        inp.write(tmp);
        // Then do while until inp rdy
        do{
            wait();
        } while(!inp_rdy.read());
        // Then deassert input valid
        inp_vld.write(0);
        wait();
    }
}

void tb::sink(){
    sc_int<16> indata;
    // Handshake - i'm not reading output rn
    outp_rdy.write(0);

    for(int i = 0; i < 64; i++){
        outp_rdy.write(1); // Handshake - I'm ready to read output
        do{
            wait();
        }while(!outp_vld.read());
        indata = outp.read();
        outp_rdy.write(0); // Handshake - I read, no longer ready to read

        cout << i << " \t: " << indata.to_int() << endl;
        wait();
    }
    sc_stop();
}