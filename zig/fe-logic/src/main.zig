const std = @import("std");
const print = std.debug.print;
const allocator = std.heap.page_allocator;
var model_list: std.ArrayList(*c_void) = undefined;
var init_model_list = true;
pub const c_void = anyopaque;

const c = @cImport({
    @cInclude("stdio.h");
});

pub extern fn deleteModelC(modelptr: *c_void) void;
pub extern fn drawModelC(ptr: *c_void, shptr: *c_void) void;
pub export fn zigGreetings() void {
    print("hello from zig!\n", .{});
}

pub export fn addModel(modelptr: *c_void) void {
    if (init_model_list) {
        model_list = std.ArrayList(*c_void).init(allocator);
        defer model_list.deinit();
        init_model_list = false;
    }

    const res = model_list.append(modelptr);
    if (res) |val| {
        _ = val;
    } else |err| {
        print("FE_LOGIC: Error in addModel(): {any}\n", .{err});
    }
}

pub export fn getModel(index: usize) *c_void {
    if (init_model_list) {
        print("FE_LOGIC: Model_list was not initializated!", .{});
    }

    return model_list.items[index];
}

pub export fn deleteModels() void {
    for (model_list.items) |model| {
        deleteModelC(model);
    }
}

pub export fn drawModels(shptr: *c_void) void {
    for (model_list.items) |model| {
        drawModelC(model, shptr);
    }
}

pub export fn drawModel(index: usize, shptr: *c_void) void {
    drawModelC(model_list.items[index], shptr);
}

pub export fn getModelsLen() usize {
    return model_list.items.len;
}
