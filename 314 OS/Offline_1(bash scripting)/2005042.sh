#!/usr/bin/bash

if [ "$#" -ne 2 ] || [ "$1" != "-i" ]; then
    echo "Usage: $0 -i input_file.txt"
    exit 1
fi
input_file="$2"
if [ ! -f "$input_file" ]; then
    echo "Error: Input file '$input_file' not found."
    exit 1
fi

readarray -t input_category < <(tr -d '\r' < "$input_file")
use_archive="${input_category[0]}"
allowed_formats="${input_category[1]}"
allowed_langs="${input_category[2]}"
total_marks="${input_category[3]}"
penalty_output="${input_category[4]}"
working_dir="${input_category[5]}"
stdid_range="${input_category[6]}"
output_dir="${input_category[7]}"
penalty_submission="${input_category[8]}"
plagiarism_file="${input_category[9]}"
penalty_plagiarism="${input_category[10]}"

is_valid_language() {
    local file_path="$1"
    local ext="${file_path##*.}"

    if [[  " $allowed_langs " =~ " $ext " ]]; then
        return 0;
    fi

    return 1
}

run_code() {
    local in="$1"
    local out="$2"

    touch "$out"

    local ext="${in##*.}"

    case "$ext" in
        c)
            gcc "$in" -o program
            ./program > "$out"
            ;;
        cpp)
            g++ "$in" -o program
            ./program > "$out"
            ;;
        py)
            python3 "$in" > "$out"
            ;;
        sh)
            bash "$in" > "$out"
            ;;
        *)
            echo "Unsupported file type: $ext"
            return 1
            ;;
    esac

    return 0
}

diff_check() {
    local file1="$1"
    local file2="$2"

    local unmatch_count=0

    awk '{ gsub(/\r/, ""); print }' "$file1" > "${file1}.tmp"
    awk '{ gsub(/\r/, ""); print }' "$file2" > "${file2}.tmp"

    while IFS= read -r line1; do
        if ! grep -Fxq "$line1" "${file2}.tmp"; then
            unmatch_count=$((unmatch_count + 1))
        fi
    done < "${file1}.tmp"

    rm "${file1}.tmp" "${file2}.tmp"

    echo "$unmatch_count"
    return 0
}
check_plagiarism() {
    local std_id="$1"
    local file="$plagiarism_file"

    if grep -q -F "$std_id" "$file"; then
        return 0 
    else
        return 1 
    fi
}



rm -rf issues/ checked/
mkdir -p issues/ checked/
rm -f marks.csv
echo "Student Id,Marks,Marks Deducted,Total marks,Remarks" >> marks.csv

IFS=' ' read -r start_id end_id <<< "$stdid_range"



for std_id in $(seq "$start_id" "$end_id"); do
    marks_evaluated=0
    marks_deducted=0
    marks_obtained=0
    submission_file=($working_dir/$std_id.*)
    submission_folder="$working_dir/$std_id"
    remarks=""
    # echo "$std_id"
    # echo "$submission_file"
    if [ ! -e $submission_file ] && [ ! -d $submission_folder ]; then
        echo "$std_id,$marks_evaluated,$marks_deducted,$marks_obtained,missing submission" >> marks.csv
        continue
    fi
    
    extension="${submission_file##*.}"
    # echo "$extension"
    if [ "$use_archive" = "true" ]; then
        if [ -d $submission_folder ]; then
            marks_deducted=$(echo "$marks_deducted + $penalty_submission" | bc)
            remarks="Issue case #1 : No archived file (folder submitted)"
            temp_folder="$working_dir/temp"
            mv "$submission_folder" "$temp_folder"
            mkdir -p "$working_dir/$std_id"
            mv "$temp_folder" "$working_dir/$std_id"
            mv "$working_dir/$std_id/temp" "$working_dir/$std_id/$std_id"
        elif [[ ! " $allowed_formats " =~ " $extension " ]]; then
            # echo "$std_id"
            marks_deducted=$(echo "$marks_deducted + $penalty_submission" | bc)
            marks_obtained=$(echo "$marks_evaluated - $marks_deducted" | bc)
            echo "$std_id,$marks_evaluated,$marks_deducted,$marks_obtained,Issue case #2 : Invalid format" >> marks.csv
            mv "$submission_file" "issues/"
            continue
        else
            mkdir -p "$working_dir/$std_id"
            if [ "$extension" = "zip" ]; then
                unzip -n "$submission_file" -d "$working_dir/$std_id"
            elif [ "$extension" = "rar" ]; then
                unrar x "$submission_file" "$working_dir/$std_id"
            elif [ "$extension" = "tar" ]; then
                tar -xvf "$submission_file" -C "$working_dir/$std_id"
            fi
        fi
        subfolder=$(find "$working_dir/$std_id/" -mindepth 1 -maxdepth 1 -type d)
        folder_name=$(basename "$subfolder")

        if [ "$folder_name" != "$std_id" ]; then
            marks_deducted=$(echo "$marks_deducted + $penalty_submission" | bc)
            remarks="Issue case #4 : Folder name not matched"
        
        fi
        executive_file=($working_dir/$std_id/$folder_name/$std_id.*)
        if is_valid_language "$executive_file"; then
            output_file=($working_dir/$std_id/$folder_name/"$std_id"_output.txt)
            run_code "$executive_file" "$output_file";
            # cat "$output_file"
            # cat "$output_dir"
            unmatched_lines=$(diff_check "$output_dir" "$output_file");
            # echo "$unmatched_lines"
            # marks_deducted=$(echo "$marks_deducted + ($penalty_output * $unmatched_lines)" | bc)
            # echo "$marks_deducted"
            # marks_evaluated=$(echo "$total_marks - $marks_deducted" | bc)
            marks_evaluated=$(echo "$total_marks - ($penalty_output * $unmatched_lines)" | bc)
            if check_plagiarism "$std_id"; then
                marks_obtained=$(echo "scale=2; ($total_marks * $penalty_plagiarism / 100) * -1" | bc)
                remarks="Plagiarism detected"
                echo "here"
            else
                marks_obtained=$(echo "$marks_evaluated - $marks_deducted" | bc)
            fi
            echo "$std_id,$marks_evaluated,$marks_deducted,$marks_obtained,$remarks" >> marks.csv
            mv "$working_dir/$std_id" "checked/"
        else
            marks_deducted=$(echo "$marks_deducted + $penalty_submission" | bc)
            marks_obtained=$(echo "$marks_evaluated - $marks_deducted" | bc)
            echo "$std_id,$marks_evaluated,$marks_deducted,$marks_obtained,Issue case #3 : Invalid programming language" >> marks.csv
            mv "$working_dir/$std_id" "issues/"
            continue
        fi
    else
        echo "here"
        echo "$submission_file"
        mkdir -p "$working_dir/$std_id";
        mv "$submission_file" "$working_dir/$std_id"
        executive_file=($working_dir/$std_id/$std_id.*)
        if is_valid_language "$executive_file"; then
            output_file=($working_dir/$std_id/$folder_name/"$std_id"_output.txt)
            run_code "$executive_file" "$output_file";
            
            unmatched_lines=$(diff_check "$output_dir" "$output_file");
            
            marks_evaluated=$(echo "$total_marks - ($penalty_output * $unmatched_lines)" | bc)
            if check_plagiarism "$std_id"; then
                marks_obtained=$(echo "scale=2; ($total_marks * $penalty_plagiarism / 100) * -1" | bc)
                remarks="Plagiarism detected"
                echo "here"
            else
                marks_obtained=$(echo "$marks_evaluated - $marks_deducted" | bc)
            fi
            echo "$std_id,$marks_evaluated,$marks_deducted,$marks_obtained,$remarks" >> marks.csv
            mv "$working_dir/$std_id" "checked/"
        else
            marks_deducted=$(echo "$marks_deducted + $penalty_submission" | bc)
            marks_obtained=$(echo "$marks_evaluated - $marks_deducted" | bc)
            echo "$std_id,$marks_evaluated,$marks_deducted,$marks_obtained,Issue case #3 : Invalid programming language" >> marks.csv
            mv "$working_dir/$std_id" "issues/"
            continue
        fi
    fi
done