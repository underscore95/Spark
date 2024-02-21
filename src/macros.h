#pragma once

/*
* Deletes the copy and move constructors for a class.
* 
* \param class The class whose constructors should be deleted
*/
#define DELETE_COPY_MOVE_CONSTRUCTORS(Class) \
    Class(const Class&) = delete; \
    Class(Class&&) = delete; \
    Class& operator=(const Class&) = delete; \
    Class& operator=(Class&&) = delete;