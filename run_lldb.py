import lldb
def run(debugger, command, result, internal_dict):
    target = debugger.CreateTarget("./build/SlotGameQt")
    process = target.LaunchSimple(None, None, None)
    state = process.GetState()
    if state == lldb.eStateStopped:
        thread = process.GetThreadAtIndex(0)
        print(f"Stop reason: {thread.GetStopDescription(256)}")
        for frame in thread:
            print(f"{frame.GetFunctionName()} at {frame.GetLineEntry().GetFileSpec().GetFilename()}:{frame.GetLineEntry().GetLine()}")
def __lldb_init_module(debugger, internal_dict):
    debugger.HandleCommand('command script add -f run_lldb.run run_test')
