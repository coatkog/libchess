#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <libchess/piece.h>

class Sprites {
  public:
    Sprites(float piece_width);

    void Create();

    void CreateFromTexture(sf::Sprite& sprite,
                           libchess::PieceColor piece_color,
                           libchess::PieceType piece_type);

    sf::Sprite& GetWhiteKingSprite();
    sf::Sprite& GetWhiteQueenSprite();
    sf::Sprite& GetWhiteRookSprite();
    sf::Sprite& GetWhiteBishopSprite();
    sf::Sprite& GetWhiteKnightSprite();
    sf::Sprite& GetWhitePawnSprite();

    sf::Sprite& GetBlackKingSprite();
    sf::Sprite& GetBlackQueenSprite();
    sf::Sprite& GetBlackRookSprite();
    sf::Sprite& GetBlackBishopSprite();
    sf::Sprite& GetBlackKnightSprite();
    sf::Sprite& GetBlackPawnSprite();

  private:
    static constexpr int kTexturePieceWidth = 320;

    float _piece_width;

    sf::Texture _texture;

    sf::Sprite _white_king_sprite;
    sf::Sprite _white_queen_sprite;
    sf::Sprite _white_rook_sprite;
    sf::Sprite _white_bishop_sprite;
    sf::Sprite _white_knight_sprite;
    sf::Sprite _white_pawn_sprite;

    sf::Sprite _black_king_sprite;
    sf::Sprite _black_queen_sprite;
    sf::Sprite _black_rook_sprite;
    sf::Sprite _black_bishop_sprite;
    sf::Sprite _black_knight_sprite;
    sf::Sprite _black_pawn_sprite;
};
