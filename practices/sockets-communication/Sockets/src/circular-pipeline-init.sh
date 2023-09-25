#!/bin/bash

javac circular/pipeline/Pipeline.java

TOTAL_PROCESS=4

java circular.pipeline.Pipeline 0 "$TOTAL_PROCESS" &
java circular.pipeline.Pipeline 1 "$TOTAL_PROCESS" & 
java circular.pipeline.Pipeline 2 "$TOTAL_PROCESS" & 
java circular.pipeline.Pipeline 3 "$TOTAL_PROCESS"
