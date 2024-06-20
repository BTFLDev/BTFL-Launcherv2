#ifndef __GAZE_HPP__
#define __GAZE_HPP__

#include <algorithm>
#include <mutex>
#include <vector>

namespace gaze {

class subject;
class watcher;
template <typename T>
class source;

class subject {
public:
    inline virtual ~subject() {}

private:
    virtual void notify_watchers();

    void add_watcher(watcher* w);
    void remove_watcher(const watcher* w);

private:
    std::mutex watcher_mutex;
    std::vector<watcher*> watchers{};

    friend class watcher;
    template <typename T>
    friend class source;
};

class watcher : public subject {
public:
    inline watcher() {}
    virtual ~watcher();

protected:
    inline virtual void subject_updated(const subject* subj) {}

    void watch(subject* subj);
    void unwatch(subject* subj);

    template <typename T>
    T* watch_assign(T* subj);

private:
    virtual void notify_watchers() override;

private:
    std::mutex subject_mutex;
    std::vector<subject*> subjects;

    friend class subject;
};

template <typename T>
class source : public subject {
public:
    source() {}
    source(const T& initialValue, watcher* owner = nullptr);

    void set(const T& value);
    const T& get();

private:
    T value;
    std::mutex value_mutex;
};

inline void subject::notify_watchers() {
    std::lock_guard guard{this->watcher_mutex};

    for (const auto& w : this->watchers) {
        w->subject_updated(this);
    }
}

inline void subject::add_watcher(watcher* w) {
    if (w == nullptr) {
        return;
    }

    std::lock_guard guard{this->watcher_mutex};
    this->watchers.push_back(w);
}

inline void subject::remove_watcher(const watcher* w) {
    std::lock_guard guard{this->watcher_mutex};

    auto found = std::find(this->watchers.begin(), this->watchers.end(), w);
    if (found != this->watchers.end()) {
        this->watchers.erase(found);
    }
}

inline watcher::~watcher() {
    for (const auto& subj : this->subjects) {
        this->unwatch(subj);
    }
}

inline void watcher::watch(subject* subj) {
    if (subj == this || subj == nullptr) {
        return;
    }

    subj->add_watcher(this);

    std::lock_guard guard{this->subject_mutex};
    this->subjects.push_back(subj);
}

template <typename T>
inline T* watcher::watch_assign(T* subj) {
    this->watch(subj);
    return subj;
}

inline void watcher::unwatch(subject* subj) {
    if (subj == nullptr) {
        return;
    }
    subj->remove_watcher(this);
}

inline void watcher::notify_watchers() {
    subject::notify_watchers();
    this->subject_updated(this);
}

template <typename T>
inline source<T>::source(const T& initialValue, watcher* owner) {
    if (owner != nullptr) {
        this->add_watcher(owner);
    }
    this->value = initialValue;
}

template <typename T>
inline void source<T>::set(const T& value) {
    std::lock_guard guard{this->value_mutex};
    this->value = value;
    this->notify_watchers();
}

template <typename T>
inline const T& source<T>::get() {
    std::lock_guard guard{this->value_mutex};
    return this->value;
}

}  // namespace gaze

#endif  // __GAZE_HPP__
