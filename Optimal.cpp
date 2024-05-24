#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_PAGES = 100;
const int MAX_FRAMES = 10;

int findOptimalPage(int pages[], int frames[], int numFrames, int numPages, int currentIndex) {
    int farthest = currentIndex;
    int pageToReplace = -1;

    for (int i = 0; i < numFrames; i++) {
        int j;
        for (j = currentIndex; j < numPages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pageToReplace = i;
                }
                break;
            }
        }

        if (j == numPages) {
            return i;
        }
    }
    return (pageToReplace == -1) ? 0 : pageToReplace;
}

int main() {
    int numFrames, numPages;
    cout << "Enter the number of frames: ";
    cin >> numFrames;

    cout << "Enter the number of pages: ";
    cin >> numPages;

    int pages[MAX_PAGES];
    int frames[MAX_FRAMES] = {0};
    bool isFrameFull[MAX_FRAMES] = {false};

    cout << "Enter the page reference string: ";
    for (int i = 0; i < numPages; i++) {
        cin >> pages[i];
    }

    int pageFaults = 0;

    for (int i = 0; i < numPages; i++) {
        bool pageFound = false;


        for (int j = 0; j < numFrames; j++) {
            if (isFrameFull[j] && frames[j] == pages[i]) {
                pageFound = true;
                break;
            }
        }


        if (!pageFound) {
            pageFaults++;
            bool replaced = false;

            // Find an empty frame to place the new page
            for (int j = 0; j < numFrames; j++) {
                if (!isFrameFull[j]) {
                    frames[j] = pages[i];
                    isFrameFull[j] = true;
                    replaced = true;
                    break;
                }
            }

            // If no empty frame is found, replace the optimal page
            if (!replaced) {
                int optimalIndex = findOptimalPage(pages, frames, numFrames, numPages, i + 1);
                frames[optimalIndex] = pages[i];
            }
        }

        // Print the current state of frames
        cout << "Page: " << pages[i] << " | Frames: ";
        for (int j = 0; j < numFrames; j++) {
            if (isFrameFull[j]) {
                cout << frames[j] << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }

    cout << "Total page faults: " << pageFaults << endl;

    return 0;
}
