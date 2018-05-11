#ifndef __FONT_HPP__
#define __FONT_HPP__

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;


// only generate image

namespace kurff{
    class Fonts{
        public:
            Fonts(int height, int width):height_(height), width_(width){
                error_ = FT_Init_FreeType( &library_ );
                img_ = Mat::zeros(height,width,CV_8UC1);
            }
            ~Fonts(){
                FT_Done_Face    ( face_ );
                FT_Done_FreeType( library_ );
            }

            void draw_bitmap( FT_Bitmap* bitmap, FT_Int x, FT_Int y){
                FT_Int  i, j, p, q;
                FT_Int  x_max = x + bitmap->width;
                FT_Int  y_max = y + bitmap->rows;
                for ( i = x, p = 0; i < x_max; i++, p++ )
                {
                    for ( j = y, q = 0; j < y_max; j++, q++ )
                    {
                        if ( i < 0      || j < 0       ||
                        i >= width_ || j >= height_ )
                        continue;
                        img_.at<uchar>(j,i)= (bitmap->buffer[q * bitmap->width + p]);
                    }
                }
            }

            void init(string font_type){
                error_ = FT_New_Face( library_, font_type.c_str(), 0, &face_ );
                error_ = FT_Set_Char_Size( face_, 50 * 64, 0, 100, 0 );                /* set character size */
                slot_ = face_->glyph;
            }

            void draw(string text, int index){
                img_.setTo(0);
                error_ = FT_Load_Char( face_, text[index], FT_LOAD_RENDER );
                int x_m = ( slot_->bitmap.width)/2;
                int y_m = ( slot_->bitmap.rows)/2;
                draw_bitmap( &slot_->bitmap,
                width_/2-x_m,
                height_/2 - y_m );
                //std::cout<< "bitmap_left: " << slot_->bitmap_left <<"bitmap_right: "<< slot_->bitmap_top;
            }
            Mat& get(){
                return img_;
            }
        protected:     
            FT_Library    library_;
            FT_Face       face_;
            FT_GlyphSlot  slot_;
            FT_Matrix     matrix_;                 /* transformation matrix */
            FT_Vector     pen_;                    /* untransformed origin  */
            FT_Error      error_;
            Mat img_ ;
            int height_;
            int width_;
};








}






#endif