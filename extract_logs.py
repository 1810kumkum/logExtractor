import sys
import os

LOG_FILE = "logs.txt"  # Path to the log file
OUTPUT_DIR = "output"   # Directory to store extracted logs

def extract_logs(date):
    """Extracts logs for a specific date and writes to an output file."""
    output_file = os.path.join(OUTPUT_DIR, f"output_{date}.txt")
    os.makedirs(OUTPUT_DIR, exist_ok=True)  # Ensure output directory exists

    try:
        with open(LOG_FILE, "r", encoding="utf-8") as infile, open(output_file, "w", encoding="utf-8") as outfile:
            buffer = []
            buffer_size = 10000  # Adjust based on memory
            prefix = date + " "  # Optimized filtering by date prefix

            for line in infile:
                if line.startswith(prefix):  # Fast check for the date
                    buffer.append(line)
                    if len(buffer) >= buffer_size:
                        outfile.writelines(buffer)  # Batch write to optimize disk writes
                        buffer.clear()

            if buffer:
                outfile.writelines(buffer)  # Write remaining logs

        print(f"✅ Logs for {date} saved to {output_file}")

    except FileNotFoundError:
        print(f"❌ Error: Log file {LOG_FILE} not found.")
    except Exception as e:
        print(f"❌ Unexpected error: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python extract_logs.py YYYY-MM-DD")
        sys.exit(1)
    
    extract_logs(sys.argv[1])
