Git Training

Prerequisites:
Download 'Git Bash': https://git-scm.com/downloads


STEP1) Choose a working directory
	*) Clone Git Repository from https://github.com/AKD1012/schulung

STEP2) Create a new Branch that references to remote 'origin/git_schulung_1'. Name the local branch also 'git_schulung_1'

STEP3) Rebase your local Branch on 'origin/master'
	*) Check with 'git status' and 'git log' how your Branch looks now and what changed
	
STEP4) Make changes in file 'main.cpp' (It doesn't need to be useful)
	*) Commit the changes to your local Branch
	*) Check with 'git status' the state of your branch
	*) Check with 'git log' your Commits
	*) Make, if wanted, more commits to see what changes in your branch
	
STEP5) Create a new branch out of the actual state (Choose a name yourself)
	*) Switch to the newly created branch
	*) Check with 'git status' and 'git log' the state of your branch

STEP6) Switch back to local Branch 'git_schulung_1'
	*) Reset your Branch back to the state of 'origin/git_schulung_1'
	*) Also make sure to drop your local modifications (if any exist) with the reset
	
STEP7) Merge your Created Branch (From STEP5) with Branch 'git_schulung_1'

STEP8) Create a new Branch that references to remote 'origin/git_schulung_2'.  Name the local branch also 'git_schulung_2'
	*) Reset your local branch to Commit '410dccfc479e35ceef29b6f4910181556f23e1d8'
	*) Check with 'git status' what changed
	*) Make some local changes and commit them
	*) Check with 'git status' what changed
	*) Try to pull the changes
		*) Commit the merge commit
		
STEP9) Reset your local Branch 'git_schulung_2' to 'origin/git_schulung_2'
	*) Reset your local branch to Commit '410dccfc479e35ceef29b6f4910181556f23e1d8'
	*) Check with 'git status' what changed
	*) Make some local changes and commit them
	*) Check with 'git status' what changed
	*) Try to pull the changes from remote, without producing a merge commit 
