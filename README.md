# omega
Omega is designed to run in EL3 and provide services to software in EL1 on Raspberry Pi-3B (ARMv8-A). Omega loads the deltaV hypervisor in EL2 and provides storage services to software being scheduled in EL1.

<img width="1031" alt="Screenshot 2024-01-31 at 13 39 17" src="https://github.com/yuvraj1803/omega/assets/37622719/d2940f70-6f57-460f-aeb2-2da66b00ba2c">

# ocom Interface
  +  Software running in EL1 (deltaOS) can communicate with Omega using Secure Monitor Calls (SMC).
  +  Function IDs 0 and 1 are utilised in this implementation for storing and loading a particular page.
  +  The page's virtual address provided needs to be present in the VM's IPA.
  +  The machine's EMMC is configured and the SD card is used to sandbox a VM's data. On a more serious implementation, a network attached storage can be used to achieve better isolation.
  +  On a Secure Monitor call in EL1, the control reaches VBAR_EL3 + 0x400, this is where the OCOM handlers are placed. Check monitor/exceptions.S
    
![Screenshot 2024-02-02 at 21 45 59](https://github.com/yuvraj1803/omega/assets/37622719/3a18333a-d71f-4970-8a79-fe8809d19e2c)

# EL3 and EL1 configuration
  + The configuration for EL3 can be found in include/config.h and EL2's configuration can be found in deltaV/include/config.h.
  + Necessary configuration for this implementation would be HCR_EL2.TSC = 0 and SCR_EL3.SMD = 0.

 # Build Dependencies
    + make
    + qemu-system-aarch64
    + gcc-aarch64-linux-gnu
    
 # Debug Dependencies
    + gdb-multiarch
    
 # How to use?
    + chmod +x install.sh
    + ./install.sh
    + make run
    
 # How to Debug?
    + make debug
    + (Another Terminal) make gdb
