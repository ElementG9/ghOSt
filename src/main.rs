#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(ghOSt::test_runner)]
#![reexport_test_harness_main = "test_main"]

use bootloader::{entry_point, BootInfo};
use core::panic::PanicInfo;
use ghOSt::{hlt_loop, memory::BootInfoFrameAllocator, println};
use x86_64::{
    structures::paging::{MapperAllSizes, Page, PageTable},
    VirtAddr,
};

entry_point!(kernel_main);

pub fn kernel_main(boot_info: &'static BootInfo) -> ! {
    ghOSt::init();

    let phys_mem_offset = VirtAddr::new(boot_info.physical_memory_offset);
    let mut mapper = unsafe { ghOSt::memory::init(phys_mem_offset) };
    let mut frame_allocator = unsafe { BootInfoFrameAllocator::init(&boot_info.memory_map) };

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
