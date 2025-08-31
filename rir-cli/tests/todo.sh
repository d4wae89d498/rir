#!/usr/bin/env bash
set -euo pipefail

# Define the RIR script path relative to this script’s directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RIR="$SCRIPT_DIR/../rir"

# Run a command and check it returns 0
if "$RIR" test.rir -tprint; then
  echo "Assertion passed: $RIR -v exited with 0"
else
  echo "Assertion failed: $RIR -v did not exit with 0 but $?" >&2
  exit 1
fi
