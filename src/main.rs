#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(ghOSt::test_runner)]
#![reexport_test_harness_main = "test_main"]

extern crate alloc;

use bootloader::{entry_point, BootInfo};
use core::panic::PanicInfo;
use ghOSt::{
    allocator,
    memory::{self, BootInfoFrameAllocator},
    println,
    task::{self, simple_executor::SimpleExecutor, Task},
};
use x86_64::VirtAddr;

entry_point!(kernel_main);

pub fn kernel_main(boot_info: &'static BootInfo) -> ! {
    println!("Hello World{}", "!");
    ghOSt::init();

    let phys_mem_offset = VirtAddr::new(boot_info.physical_memory_offset);
    let mut mapper = unsafe { memory::init(phys_mem_offset) };
    let mut frame_allocator = unsafe { BootInfoFrameAllocator::init(&boot_info.memory_map) };

    allocator::init_heap(&mut mapper, &mut frame_allocator).expect("heap initialization failed");

    #[cfg(test)]
    test_main();

    let mut executor = SimpleExecutor::new();
    executor.spawn(Task::new(task::keyboard::print_keypresses()));
    executor.run();
    ghOSt::hlt_loop()
}

#[cfg(not(test))]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("{}", info);
    ghOSt::hlt_loop()
}

#[cfg(test)]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    ghOSt::test_panic_handler(info)
}
