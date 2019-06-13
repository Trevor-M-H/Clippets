#Clippets  

/*

  DISCLAIMER and Copyright

  Free to use!
  
  I accept not responsibility for the use or misuse of this software.
  
  Please credit the Author if you do want to use it.
  
  Trevor Heyl 2009

*/

Some useful C-code for embedded use. Most of it is nicely configurable and reusable.

+---------+
| Modules |
+---------+

*************
* tmh_timer *
*************

General purpose timer functions. Needs a timer tick, you can add, remove timers.
Timers can be one shot or reloadable. there is also a timer callback mechanism.
the module is very configurable to allow tight code.

*************
* tmh_buffer *
*************
Circular / ring buffer implementation. Has push, pop, init functions.  Very small code. Application supplied buffer
array via init function. Very configurable, can specify 8 or 16 bit data buffers and 8 or 16 bit bufffer
sizes (pointers).

New

