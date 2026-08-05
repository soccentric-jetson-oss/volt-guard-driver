#include "libvolt-guard.h" <stdio.h> <errno.h>
int p=0,f=0;
#define T(n) do{printf("  TEST: %s ... ",n);fflush(stdout);}while(0)
#define P() do{printf("PASS\n");p++;}while(0)
#define F(m) do{printf("FAIL: %s\n",m);f++;}while(0)
#define S() do{printf("SKIP\n");}while(0)
int main(){
    printf("Volt Guard Driver Test Suite\n");
    T("open/close");struct volt_guard_handle*h=volt_guard_open("/dev/volt-guard0");if(!h){S();}else{volt_guard_close(h);P();}
    T("set mode");h=volt_guard_open("/dev/volt-guard0");if(!h){S();}else{int r=volt_guard_set_mode(h,1,15000);if(r){volt_guard_close(h);F("set");}else{volt_guard_close(h);P();}}
    T("get sensors");h=volt_guard_open("/dev/volt-guard0");if(!h){S();}else{int32_t t;uint32_t v,c,pw;int r=volt_guard_get_sensors(h,&t,&v,&c,&pw);if(r){volt_guard_close(h);F("sensors");}else{volt_guard_close(h);P();}}
    T("invalid args");int r=volt_guard_set_mode(NULL,0,0);if(r==-EINVAL)P();else F("expected -EINVAL");
    printf("\n%d passed, %d failed\n",p,f);return f>0?1:0;
}
