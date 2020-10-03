# Bootloader testcase

1. `# Clean flash`
2. `make -C bootloader flash` `# Load bootloader`
3.  `# reboot device`
    * Press right
    * Press left
    * Wait 0.1 s
    * Release left
    * Release right
4. Wait 0.5 s
5. `# Expect no FW`
    * Expect: no uart welcome message
    * Expect: red led on
    * Expect: no USB
6. `# reboot device and go to DFU`
    * Press left 
    * Press right
    * Wait 0.1 s
    * Release left
    * Wait 0.5 s 
    * Release right
7. Wait 0.5 s
8. `# Expect DFU`
    * Expect: blue led on
    * Expect: USB: DFU
9. `target_f2/deploy-dfu.sh` `# load FW`
10. `# reboot device`
    * Press right
    * Press left
    * Wait 0.1 s
    * Release left
    * Release right
11. Wait 0.5 s
12. `# Expect FW`
    * Expect: uart welcome message
    * Expect: USB Flipper CDC

# Input testcase

1. `docker-compose exec dev make -C target_f2 example_input_dump`
2. Flash
3. For x in ```
[
    (Up, "00"),
    (Down, "01"),
    (Right, "02"),
    (Left, "03"),
    (Ok, "04"),
    (Back, "05"),
]
```
    * Press ${x[0]}
    * wait 0.05
    * Expect: Uart: "event: ${x[1]} pressed"
    * wait 0.05
    * Release ${x[0]}
    * wait 0.05
    * Expect: Uart: "event: ${x[1]} released"
    * wait 0.05

TODO: add debouncing check (multiple press and check there is no multiple events)