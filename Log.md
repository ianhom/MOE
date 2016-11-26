# Log
##26th Nov 2016
Update design record about portable.

##24th Nov 2016
Fix the bug in PT.h, extend the range of running point which stores the line number of last running.

##22nd Nov 2016
Fix the bug of debug.h

##21st Nov 2016
Update project code of Nucleo-STM32L011K4

##19th Nov 2016
Update API-description

##18th Nov 2016
Port MOE on Nucleo-STM32L011K4

##17th Nov 2016
Port MOE on KL27-MiniBoard

##12th Nov 2016
Add more descriptions to introduction.

##7th Nov 2016
Add API description.

##5th Nov 2016
Fix some bug with new event structure

##4th Sep 2016
Modify timer with new event structure

##31st Aug 2016
First contribution from Joe, thank  you!!

##30th Aug 2016
Complete the modification of message

##28th Aug 2016
Try a new way for a better message

##24th Aug 2016
Merge the new way for a better timer.

##23rd Aug 2016
Try a new way to improve timer.

##22nd Aug 2016
Add "Check if" into queue.

##21st Aug 2016
Add "assert" and "check if" into core, message, event, timer.

## 17th Aug 2016
Add assert MACRO

## 16th Aug 2016
Modify the event queue block deleting method, delete the added block.

## 10th Aug 2016
100-days!!

## 8th Aug 2016
Fix the bug for flexible length event queue.

## 5th Aug 2016
Add task name printing function.

## 1st Aug 2016
Modify uart driver of KL25, use Rx interrupt to receive entire telegram.

## 25th Jul 2016
Debug 11xx and finish sending.

## 21st Jul 2016
Add driver of 11xx

## 20th Jul 2016
Add uart driver of KL25

## 15th Jul 2016
Add a demo app to use cc1101 driver for sending and receiving

## 14th Jul 2016
Add CC1101 driver

## 8th Jul 2016
Add PT application

## 3rd Jul 2016
Use x macro to simplize the interface bewteen core and tasks.   
And create board configuration files for hardware configuration.

## 1st Jul 2016
Modify all app modules

## 29th Jun 2016
Make user interface more easier to configure.

## 27th Jun 2016
Add message never receiving check.

## 22rd Jun 2016
Re-design the events and scheduler, name it MOE :sunglasses:

## 12th Jun 2016
Improve & complete queue process

## 6th Jun 2016
Solve the #5 issue. 

## 5th Jun 2016
Finish message works, ready to debug. 

## 26th May 2016
Start message works. 

## 25th May 2016
Make some flexible malloc options. 

## 24th May 2016
Make some flexible debug options.   

## 23rd May 2016
Timer debugging complete.   
- [x] Debug timer code

## 20th May 2016
Start debug the timer.

## 9th May 2016
Still work with software timers, add some test functions, **un-debugged**.

## 7th May 2016
Timer is added, however **the code is NOT debug yet**. Please wait for the updating.

## 5th May 2016
[百度](http://www.baidu.com)   
![baidu](https://ss0.bdstatic.com/5aV1bjqh_Q23odCf/static/superman/img/logo/bd_logo1_31bdc765.png)
> -百度一下会死啊！ 
> -会。。。

## 4th May 2016
I have finished the basical parts of schudeler function, I use 3 tasks and set event to each others, it works. Also I add debug print MACROs with maybe useful. I will add software timer in next step.

