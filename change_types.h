#pragma once

const enum class CHANGE_TYPE {
    MOVE, SIZE, COLOR, CREATE, DESTROY
};

const std::map<CHANGE_TYPE, std::string> debug_action_output{
        {CHANGE_TYPE::CREATE, "Create"},
        {CHANGE_TYPE::SIZE, "Size"},
        {CHANGE_TYPE::MOVE, "Move"},
        {CHANGE_TYPE::COLOR, "Color"},
        {CHANGE_TYPE::DESTROY, "Destroy"}

};