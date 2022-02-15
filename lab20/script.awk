#!/usr/bin/env awk
{
    
    else if ($0 ~ /^path_to_csv_reports[[:space:]]*=/) {
        print "path_to_csv_reports = /reports";
        next;
    }
    else if ($0 ~ /^DbType[[:space:]]*=/) {
        print "DbType = DATABASE";
        next;
    }
    else if ($0 ~ /^DataDir[[:space:]]*=/) {
        print "DataDir = /data";
        next;
    }
    else if ($0 ~ /^DumpDir[[:space:]]*=/) {
        print "DumpDir = /dumps";
        next;
}