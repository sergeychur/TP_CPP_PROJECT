//
// Created by sergey on 19.10.18.
//

#ifndef SERVER_UPDATE_MAKER_HPP
#define SERVER_UPDATE_MAKER_HPP

#include "news_taker.hpp"
#include "update.hpp"

class UpdateMaker : public NewsTaker {
    public:
        UpdateMaker();
        UpdateMaker(const UpdateMaker&) = delete;
        UpdateMaker(const UpdateMaker&&) = delete;
        UpdateMaker& operator=(UpdateMaker&) = delete;
        UpdateMaker&& operator=(UpdateMaker&&) = delete;

        void handle_event(UpdateLine&) override;
        std::shared_ptr<Update>&& get_update() override;
        void delete_update() override;
        ~UpdateMaker() override;
    private:
        std::shared_ptr<Update> update;

};

#endif //SERVER_UPDATE_MAKER_HPP
