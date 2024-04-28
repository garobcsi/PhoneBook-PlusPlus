import subprocess

def record_input(process):
    with open('input_log.txt', 'a') as log_file:
        while True:
            try:
                user_input = input()
                log_file.write(user_input + '\n')
                log_file.flush()
                process.stdin.write(user_input.encode() + b'\n')
                process.stdin.flush()
            except KeyboardInterrupt:
                break

def run_terminal_program():
    process = subprocess.Popen(['./cmake-build-debug/PhoneBook'], stdin=subprocess.PIPE)
    return process

if __name__ == "__main__":
    try:
        print("Launching terminal program...")
        process = run_terminal_program()
        print("Terminal program launched.")
        record_input(process)
    except KeyboardInterrupt:
        pass
    except Exception as e:
        print("An error occurred:", e)
    finally:
        if process:
            process.terminate()
        print("Recording inputs...")
