const std = @import("std");
const print = std.debug.print;

pub export fn zigGreetings() void {
    print("hello from zig!\n", .{});
}
