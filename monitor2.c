#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function to display menu header */
void showHeader() {
    printf("\n========================================\n");
    printf("   PROCESS MONITORING DASHBOARD\n");
    printf("========================================\n");
}

/* 1. Display all processes using ps command */
void showAllProcesses() {
    printf("\n--- RUNNING PROCESSES (ps aux) ---\n");
    system("ps aux | head -20");
}

/* 2. Live monitoring using top command */
void liveMonitor() {
    printf("\n--- LIVE MONITOR (top) ---\n");
    system("top -n 1 | head -15");
}

/* 3. Create child process using fork() system call */
void createChild() {
    pid_t pid = fork();
    
    if(pid == 0) {
        printf("\n[CHILD] PID: %d\n", getpid());
        printf("[CHILD] Parent PID: %d\n", getppid());
        printf("[CHILD] Sleeping for 5 seconds...\n");
        sleep(5);
        printf("[CHILD] Exiting now\n");
        exit(0);
    }
    else if(pid > 0) {
        printf("\n[PARENT] PID: %d\n", getpid());
        printf("[PARENT] Created Child PID: %d\n", pid);
        printf("[PARENT] Waiting for child...\n");
        wait(NULL);
        printf("[PARENT] Child finished\n");
    }
    else {
        printf("Fork failed!\n");
    }
}

/* 4. Kill process using kill() system call */
void killProcess() {
    int pid, sig;
    
    printf("\n--- KILL PROCESS ---\n");
    printf("Signals:\n");
    printf("  2 = SIGINT (Ctrl+C)\n");
    printf("  9 = SIGKILL (Force)\n");
    printf(" 15 = SIGTERM (Normal)\n");
    
    printf("\nEnter PID: ");
    scanf("%d", &pid);
    
    printf("Enter Signal: ");
    scanf("%d", &sig);
    
    if(kill(pid, sig) == 0)
        printf("Signal %d sent to PID %d\n", sig, pid);
    else
        printf("Failed to kill process\n");
}

/* 5. Kill process by name using pkill */
void killByName() {
    char name[50];
    
    printf("\n--- KILL BY NAME ---\n");
    printf("Enter process name: ");
    scanf("%s", name);
    
    char cmd[100];
    sprintf(cmd, "pkill %s", name);
    
    if(system(cmd) == 0)
        printf("Killed all %s processes\n", name);
    else
        printf("No process found with name %s\n", name);
}

/* 6. Background process demo using & operator */
void backgroundDemo() {
    printf("\n--- BACKGROUND PROCESS ---\n");
    printf("Starting sleep 30 in background...\n");
    system("sleep 30 &");
    printf("Background process started\n");
    system("jobs -l");
    printf("\nTo bring to foreground: fg %%1\n");
    printf("To send to background: bg %%1\n");
}

/* 7. Show current process info */
void showInfo() {
    printf("\n--- CURRENT PROCESS INFO ---\n");
    printf("This Program PID: %d\n", getpid());
    printf("Parent PID: %d\n", getppid());
    printf("User ID: %d\n", getuid());
}

/* Main function - Dashboard menu */
int main() {
    int choice;
    
    while(1) {
        showHeader();
        printf("1. Show Processes (ps)\n");
        printf("2. Live Monitor (top)\n");
        printf("3. Create Child Process (fork)\n");
        printf("4. Kill Process (kill)\n");
        printf("5. Kill by Name (pkill)\n");
        printf("6. Background Process (bg/fg)\n");
        printf("7. Process Info\n");
        printf("8. Exit\n");
        printf("\nChoice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: showAllProcesses(); break;
            case 2: liveMonitor(); break;
            case 3: createChild(); break;
            case 4: killProcess(); break;
            case 5: killByName(); break;
            case 6: backgroundDemo(); break;
            case 7: showInfo(); break;
            case 8: 
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\nPress Enter...");
        getchar();
        getchar();
    }
    
    return 0;
}
