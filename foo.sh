#!/bin/bash

teams=("Team A" "Team B" "Team C" "Team D")
total_teams=${#teams[@]}
total_matches=$((total_teams * (total_teams - 1)))

declare -A scores

# Initialize scores
for team in "${teams[@]}"; do
  scores["$team"]=0
done

# Generate fixture
fixture=()
for ((i=0; i<total_teams-1; i++)); do
  for ((j=i+1; j<total_teams; j++)); do
    fixture+=("${teams[$i]} vs ${teams[$j]}")
  done
done

# Play matches
for match in "${fixture[@]}"; do
  home_team=$(echo "$match" | awk -F' vs ' '{print $1}')
  away_team=$(echo "$match" | awk -F' vs ' '{print $2}')

  # Simulate match result (you can modify this part)
  home_score=$((RANDOM % 5))
  away_score=$((RANDOM % 5))

  echo "$home_team $home_score - $away_team $away_score"

  # Update scores
  if [[ $home_score -gt $away_score ]]; then
    scores["$home_team"]=$((scores["$home_team"] + 3))
  elif [[ $home_score -lt $away_score ]]; then
    scores["$away_team"]=$((scores["$away_team"] + 3))
  else
    scores["$home_team"]=$((scores["$home_team"] + 1))
    scores["$away_team"]=$((scores["$away_team"] + 1))
  fi
done

# Display final scores
echo "Final Scores:"
for team in "${teams[@]}"; do
  echo "$team: ${scores["$team"]} points"
done

