#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <libchess/piece.h>

class sprites {
  public:
    sprites(float piece_width);

    void create();

    void create_from_texture(sf::Sprite& sprite,
                           libchess::piece::color piece_color,
                           libchess::piece::type piece_type);

    sf::Sprite& get_white_king_sprite();
    sf::Sprite& get_white_queen_sprite();
    sf::Sprite& get_white_rook_sprite();
    sf::Sprite& get_white_bishop_sprite();
    sf::Sprite& get_white_knight_sprite();
    sf::Sprite& get_white_pawn_sprite();

    sf::Sprite& get_black_king_sprite();
    sf::Sprite& get_black_queen_sprite();
    sf::Sprite& get_black_rook_sprite();
    sf::Sprite& get_black_bishop_sprite();
    sf::Sprite& get_black_knight_sprite();
    sf::Sprite& get_black_pawn_sprite();

  private:
    static constexpr int k_texture_piece_width = 320;

    float m_piece_width;

    sf::Texture m_texture;

    sf::Sprite m_white_king_sprite;
    sf::Sprite m_white_queen_sprite;
    sf::Sprite m_white_rook_sprite;
    sf::Sprite m_white_bishop_sprite;
    sf::Sprite m_white_knight_sprite;
    sf::Sprite m_white_pawn_sprite;

    sf::Sprite m_black_king_sprite;
    sf::Sprite m_black_queen_sprite;
    sf::Sprite m_black_rook_sprite;
    sf::Sprite m_black_bishop_sprite;
    sf::Sprite m_black_knight_sprite;
    sf::Sprite m_black_pawn_sprite;
};
