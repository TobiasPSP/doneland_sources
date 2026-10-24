#include "lab_ownership.h"
#include <assert.h>
#include <stdio.h>
using batcharger::LabOwnership;
int main(){LabOwnership owner;
 assert(!owner.owned()&&!owner.expired(100000)); // manual/web sessions never acquire a lease
 owner.claim(1,10,3,100,200);assert(!owner.expired(10199));assert(owner.expired(10200));
 assert(!owner.heartbeat(2,10,3,101,1000));assert(!owner.heartbeat(1,11,3,101,1000));
 assert(!owner.heartbeat(1,10,4,101,1000));assert(!owner.heartbeat(1,10,3,100,1000));
 assert(owner.heartbeat(1,10,3,101,1000));assert(!owner.expired(10999));
 assert(!owner.heartbeat(1,10,3,101,9000));assert(owner.expired(11000));
 assert(!owner.heartbeat(1,10,3,102,11000)); // no revival after deadline
 owner.observe(4,true);assert(!owner.owned());owner.claim(1,10,4,200,500);owner.observe(4,false);assert(!owner.owned());
 owner.claim(1,10,5,0xfffffffeu,0xfffffff0u);assert(owner.heartbeat(1,10,5,1,0x20));
 assert(!owner.expired(0x20+9999));assert(owner.expired(0x20+10000));
 puts("PASS: manual sessions, owner identity/boot/session, replay rejection, lease deadline, no late revival and wraparound");}
