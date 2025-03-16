#include <iostream>
#include <memory>
#include "mutex.hpp"

class Image {
public:
    Image(std::istream& imgSrc) {}
};

// struct to hold the data of PrettyMenu so that it can be copied easily
class PMImpl {
public:
    std::shared_ptr<Image> bgImage;
    int imageChanges;

    void swap(PMImpl& other) {
        using std::swap;
        swap(bgImage, other.bgImage);
        swap(imageChanges, other.imageChanges);
    }
};

void swap(PMImpl& a, PMImpl& b) {
    a.swap(b);
}

class PrettyMenu {
public:
    void changeBackground_unsafe(std::istream& imgSrc);
    void changeBackground_basic(std::istream& imgSrc);
    void changeBackground_strong(std::istream& imgSrc);
private:
    Mutex mutex;
    Image* bgImage;
    int imageChanges;
    // use shared_ptr to manage the lifetime of the image
    std::shared_ptr<Image> bgImage_;
    // use struct for exception-safe code
    std::shared_ptr<PMImpl> pImpl;
};

// exception-unsafe code
void PrettyMenu::changeBackground_unsafe(std::istream& imgSrc) {
    Lock::lock(&mutex);
    delete bgImage;
    // wrong: imageChanges increases even if new Image throws exception
    ++imageChanges;
    // exception-safety issue: if new Image throws exception, bgImage will not be deleted
    bgImage = new Image(imgSrc);
    // if exception is thrown, mutex will not be unlocked
    Lock::unlock(&mutex);
}

// exception-basic-safe code
void PrettyMenu::changeBackground_basic(std::istream& imgSrc) {
    // use RAII to ensure mutex is unlocked
    Lock ml(&mutex);
    // if exception is thrown, bgImage_ will not be deleted, thus keep the old image
    bgImage_.reset(new Image(imgSrc));
    // here goes some other changes on bgImage_
    // if exception is thrown half way, bgImage_ will keep partial changes  
    ++imageChanges;
}

// exception-safe code
void PrettyMenu::changeBackground_strong(std::istream& imgSrc) {
    using std::swap;
    Lock ml(&mutex);
    // copy original data
    std::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));
    // change the data
    pNew->bgImage.reset(new Image(imgSrc));
    ++pNew->imageChanges;
    // swap the new data with the old data
    swap(pImpl.get(), pNew.get());
}

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    return 0;
}