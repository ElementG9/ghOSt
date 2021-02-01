#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(ghOSt::test_runner)]
#![reexport_test_harness_main = "test_main"]

use core::panic::PanicInfo;
use ghOSt::{hlt_loop, println};

#[no_mangle]
pub extern "C" fn _start() -> ! {
    ghOSt::init();

    #[cfg(test)]
    test_main();

    hlt_loop()
}

#[cfg(not(test))]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("{}", info);
    hlt_loop()
}

#[cfg(test)]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    ghOSt::test_panic_handler(info)
}
