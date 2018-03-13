#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
  short pointer;
  int value;
} Matrix;

void smith_waterman(char* seq1, char* seq2, int seq_len1, int seq_len2,
                     int gap_penalty, int match_score, int mismatch_score) {

   int i,j;

    // print matching info:
    printf("Here are the entered strings to be matched : \n");
    printf("%s\n%s\n", seq1, seq2);
    // create and initialize scoring matrix
    Matrix** score = (Matrix**) malloc(sizeof(Matrix*) * (seq_len1 + 1));
    for(i = 0; i < seq_len1+1; i++)
        score[i] = (Matrix*) malloc(sizeof(Matrix) * (seq_len2 + 1));

    // initialize first column
    for(i = 0; i < seq_len1+1; i++) {
        if(i==0)
            {score[i][0].value = 0; score[i][0].pointer = 69;}
        else
            {score[i][0].value = score[i-1][0].value + gap_penalty;
             score[i][0].pointer = 1;}
    }

    // initialize first row
    for(i = 0; i < seq_len2+1; i++) {
        if(i==0)
            {score[0][i].value = 0; score[0][i].pointer = 69;}
        else
            {score[0][i].value = score[0][i-1].value + gap_penalty;
             score[0][i-1].pointer = -1;}
    }

    // scoring:
      for(i = 1; i < seq_len1 + 1; i++) {
          for(j = 1; j < seq_len2 + 1; j++) {
              if(seq1[i-1] == seq2[j-1])
                  score[i][j].value = score[i-1][j-1].value + match_score;
              else score[i][j].value = score[i-1][j-1].value + mismatch_score;
              score[i][j].pointer = 0;

              if(score[i-1][j].value + gap_penalty > score[i][j].value) {
                  score[i][j].value = score[i-1][j].value + gap_penalty;
                  score[i][j].pointer = 1;
              }
              if(score[i][j-1].value + gap_penalty > score[i][j].value) {
                  score[i][j].value = score[i][j-1].value + gap_penalty;
                  score[i][j].pointer = -1;
              }
              if(score[i][j].value < 0) {
                score[i][j].value = 0;
                score[i][j].pointer = 9;
              }

          }
      }

    // Printing the matrices generated:
    printf("\nThis is the scoring matrix of values generated:\n");
    for(i = 0; i < seq_len1+1; i++) {
        for(j = 0; j < seq_len2 + 1; j++) {
          printf("  %5d", score[i][j].value);
        }
        printf("\n");
    }

    printf("\n\n");

    printf("\nThis is the scoring matrix of pointers generated:\n");

    for(i = 0; i < seq_len1+1; i++) {
        for(j = 0; j < seq_len2 + 1; j++) {
          printf("  %5d", score[i][j].pointer);
        }
        printf("\n");
    }

    char aligned1[1000], aligned2[1000];
    int length = 0;
    // Print the local alignment result:
    int max = 0; int maxi, maxj;
    maxi = maxj = -1;
    for(i=0; i < seq_len1+1; i++) {
      for(j=0; j < seq_len2+1; j++) {
        if(max < score[i][j].value) {
          max = score[i][j].value;
          maxi = i;
          maxj = j;
        }
      }
    }
    printf("\n\n");
    score[0][0].pointer = 9;
    i = maxi;
    j=maxj;
    while(score[i][j].pointer != 9){
        if(score[i][j].pointer == 0) {
            // aligned1[length] = seq1[i];
            // aligned2[length] = seq2[j];
            printf("%c ----- %c", seq1[i-1], seq2[j-1]);
            if(seq1[i-1] == seq2[j-1]) printf("*\n");
            else printf("\n");
            length++; i--; j--;
        }
        else if(score[i][j].pointer == 1) {
            // aligned1[length] = seq1[i];
            // aligned2[length] = '-';
            printf("%c ----- %c\n", seq1[i-1], '|');
            length++; i--;
        }
        else if(score[i][j].pointer == -1){
            // aligned1[length] = '-';
            // aligned2[length] = seq2[j];
            printf("%c ----- %c\n", '|', seq2[j-1]);
            length++; j--;
        }
    }

  }

int main() {

    char *seq1, *seq2;
    int seq_len1, seq_len2;
    int gap_penalty, match_score, mismatch_score;

    printf("Input the length of sequence 1 :\n");
    scanf("%d", &seq_len1);
    printf("Input the length of sequence 2 :\n");
    scanf("%d", &seq_len2);

    seq1 = (char*) malloc(sizeof(char) * (seq_len1 + 2));
    seq2 = (char*) malloc(sizeof(char) * (seq_len2 + 2));

    // Flush the buffer
    int c;
    while ((c = getchar()) != EOF && c != '\n');

    printf("Input the first sequence :\n");
    fgets(seq1, seq_len1 + 1, stdin);

    // Flush the buffer
    while ((c = getchar()) != EOF && c != '\n');

    printf("Input the second sequence :\n");
    fgets(seq2, seq_len2 + 1, stdin);

    printf("Input the gap penalty :\n");
    scanf("%d", &gap_penalty);
    printf("Input the match score :\n");
    scanf("%d", &match_score);
    printf("Input the mismatch score :\n");
    scanf("%d", &mismatch_score);

    smith_waterman(seq1, seq2, seq_len1, seq_len2, gap_penalty, match_score, mismatch_score);
}
