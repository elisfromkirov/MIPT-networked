#include <server/controller.hpp>

#include <server/server.hpp>

#include <utils/random.hpp>
#include <utils/uuid.hpp>

ServerController::ServerController(World& world)
    : world_{&world},
      server_{},
      server_controlled_entities_{} {
  for (std::size_t i = 0; i < 5; ++i) {
    auto uuid = utils::UniversallyUniqueIdentifier::Next();

    server_controlled_entities_.push_back(uuid);

    auto& entity = world_->Add(uuid);
    entity.uuid = uuid;
    entity.x = utils::Random() - 0.1f;
    entity.y = utils::Random() + 0.3f;
    entity.r = utils::Random() * 0.01;
  }
}

void ServerController::SetupServer(Server* server) {
  server_ = server;
}

Entity ServerController::SetupEntity() {
  auto uuid = utils::UniversallyUniqueIdentifier::Next();

  auto& entity = world_->Add(uuid);
  entity.uuid = uuid;
  entity.x = 0.5f;
  entity.y = 0.5f;
  entity.r = 0.02f;

  return entity;
}

std::vector<Entity> ServerController::Entities() {
  std::vector<Entity> result{};
  auto& entities = world_->Entities();
  for (const auto& [uuid, entity] : entities) {
    result.push_back(entity);
  }
  return result;
}

void ServerController::Update(std::uint32_t delta_time) {
  for (auto uuid : server_controlled_entities_) {
    auto delta_x = utils::Random(true) * static_cast<float>(delta_time) * 0.001f;
    auto delta_y = utils::Random(true) * static_cast<float>(delta_time) * 0.001f;

    auto& entity = world_->Find(uuid);

    entity.x += delta_x;
    entity.y += delta_y;

    server_->Broadcast(EntityMovedEvent{uuid, delta_x, delta_y});
  }

  auto& entities = world_->Entities();
  for (auto& [lhs_uuid, lhs_entity] : entities) {
    for (auto& [rhs_uuid, rhs_entity] : entities) {
      if (lhs_uuid == rhs_uuid) {
        continue;
      }

      auto distance = 
          (lhs_entity.x - rhs_entity.x) * (lhs_entity.x - rhs_entity.x) +
          (lhs_entity.y - rhs_entity.y) * (lhs_entity.y - rhs_entity.y);

      auto min_distance = (lhs_entity.r + rhs_entity.r) * (lhs_entity.r + rhs_entity.r);

      if (distance < min_distance) {
        auto lhs_delta_x = utils::Random() - lhs_entity.x;
        auto lhs_delta_y = utils::Random() - lhs_entity.y;

        auto rhs_delta_x = utils::Random() - rhs_entity.x;
        auto rhs_delta_y = utils::Random() - rhs_entity.y;

        auto lhs_delta_r = (lhs_entity.r < rhs_entity.r ? -lhs_entity.r * 0.5f :  rhs_entity.r * 0.5f);

        auto rhs_delta_r = (lhs_entity.r < rhs_entity.r ?  lhs_entity.r * 0.5f : -rhs_entity.r * 0.5f);

        lhs_entity.x += lhs_delta_x;
        lhs_entity.y += lhs_delta_y;
        lhs_entity.r += lhs_delta_r;

        rhs_entity.x += rhs_delta_x;
        rhs_entity.y += rhs_delta_y;
        rhs_entity.r += rhs_delta_r;        

        server_->Broadcast(EntityMovedEvent{lhs_uuid, lhs_delta_x, lhs_delta_y});
        server_->Broadcast(EntityResizedEvent{lhs_uuid, lhs_delta_r});
        
        server_->Broadcast(EntityMovedEvent{rhs_uuid, rhs_delta_x, rhs_delta_y});
        server_->Broadcast(EntityResizedEvent{rhs_uuid, rhs_delta_r});
      }
    }
  }
}

void ServerController::OnPlayerEntityMovedEvent(const PlayerEntityMovedEvent& event) {
  auto& entity = world_->Find(event.uuid);
  entity.x += event.delta_x;
  entity.y += event.delta_y;
}