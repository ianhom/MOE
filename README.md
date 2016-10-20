# MOE    
![logo](https://github.com/ianhom/MOE/blob/master/Documents/Pic/MOE%20logo%20V0.1c.png)   
[中文说明](https://github.com/ianhom/MOE/blob/master/README_CHINESE.md) 
## Introduce
MOE is an event-driven scheduler system for 8/16/32-bit MCUs. Features with:   

 | Description   
----------------- | ---------------------------------------------   
**Event-driven** | Flexible event queue length, priority event supported.   
**Timer** | Useful ms-timer with callback.   
**Message** | Easy-use message API for communication between tasks, To-All-Task message with low RAM comsuption supported.   
**Debug** | Flexible debug print options for each task or module; Useful easy-assert.  
**Protothread** | Protothread is supported for application module.

## How to use
- **Step 1**: Port the MOE to your hardware, provide "system clock in ms" and "poll function", init and run MOE.      
- **Step 2**: Create your own tasks or use exist app tasks to build your application.   
- **Step 3**: Register tasks in Project_Config.h and continue other configuration in the same file.   
- **Step 4**: Run & Enjoy.   

## Special Thanks 
- MOE Logo drawing by **Miss Cai Jianan**.
