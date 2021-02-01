#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(ghOSt::test_runner)]
#![reexport_test_harness_main = "test_main"]

use core::panic::PanicInfo;
use ghOSt::println;

#[no_mangle]
pub extern "C" fn _start() -> ! {
    println!("Hello world{}", "!");

    ghOSt::init();
    x86_64::instructions::interrupts::int3();

    unsafe {
        *(0xdeadbeef as *mut u64) = 42;
    };

    fn stack_overflow() {
        stack_overflow();
    }
    stack_overflow();

    #[cfg(test)]
    test_main();

    loop {}
}

#[cfg(not(test))]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("{}", info);
    loop {}
}

#[cfg(test)]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    ghOSt::test_panic_handler(info)
}
