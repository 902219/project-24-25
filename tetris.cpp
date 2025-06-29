#include "tetris.hpp"
#include <iostream>



//classe piece

	std::istream& piece::operator>>(std::istream& is, piece& p){
		
	}


	std::ostream& operator<<(std::ostream& os, piece const& p){

	}


    piece::piece(){
    		m_side = m_color = 0;
    		m_grid = nullptr;
    }


    piece::piece(uint32_t s, uint8_t c){
    		m_side = s;
    		m_color = c;
    		m_grid = nullptr;
    }


    piece::piece(piece const& rhs){
    		m_color = rhs.m_color;
    		m_side = rhs.m_side;
    		
		    if (rhs.m_grid) {
		        m_grid = new bool*[m_side];
		        for (uint32_t i = 0; i < m_side; ++i) {
		            m_grid[i] = new bool[m_side];
		            for (uint32_t j = 0; j < m_side; ++j) {
		                m_grid[i][j] = rhs.m_grid[i][j];
		            }
		        }
		    } else {
		        m_grid = nullptr;
		    }
    }


    piece::piece(piece&& rhs){

    	m_grid = rhs.m_grid;
    	rhs.m_grid = nullptr;

    	m_side = rhs.m_side;
    	rhs.m_side = 0;

    	m_color = rhs.m_color;
    	rhs.m_color = 0;
    }


    piece::~piece(){
	    if (m_grid) {
	        for (uint32_t i = 0; i < m_side; ++i) {
	            delete[] m_grid[i];
	        }
	        delete[] m_grid;
	    }
    }


    piece& piece::operator=(piece const& rhs){
	    if (this == &rhs) return *this;

	    if (m_grid) {
	        for (uint32_t i = 0; i < m_side; ++i)
	            delete[] m_grid[i];
	        delete[] m_grid;
	    }

	    m_side = rhs.m_side;
	    m_color = rhs.m_color;

	    if (rhs.m_grid) {
	        m_grid = new bool*[m_side];
	        for (uint32_t i = 0; i < m_side; ++i) {
	            m_grid[i] = new bool[m_side];
	            for (uint32_t j = 0; j < m_side; ++j)
	                m_grid[i][j] = rhs.m_grid[i][j];
	        }
	    } else {
	        m_grid = nullptr;
	    }

	    return *this;
    }


    piece& piece::operator=(piece&& rhs){
    	if (this == &rhs) return *this;

	    if (m_grid) {
	        for (uint32_t i = 0; i < m_side; ++i)
	            delete[] m_grid[i];
	        delete[] m_grid;
	    }

	    m_side = rhs.m_side;
	    m_color = rhs.m_color;

	   	m_grid = rhs.m_grid;
	   	rhs.m_grid = nullptr;

	    return *this;
    }

    bool piece::operator==(piece const& rhs) const{
    	if(rhs.m_side != m_side || rhs.m_color != m_color) return false;
    	if((!rhs.m_grid && m_grid) || (!m_grid && rhs.m_grid)) return false;
    	if(!rhs.m_grid && !m_grid) return true;


	    for (uint32_t i = 0; i < m_side; ++i) {
		    for (uint32_t j = 0; j < m_side; ++j) {
		        if (m_grid[i][j] != rhs.m_grid[i][j]) return false;
		    }
		}     

    	return true;
    }

    bool piece::operator!=(piece const& rhs) const{
    	return !(*this==rhs);
    }

    bool& piece::operator()(uint32_t i, uint32_t j){
    	if(i > m_side || j > m_side) throw tetris_exception;
    	return &m_grid[i][j];
    }
    bool piece::operator()(uint32_t i, uint32_t j) const{
    	if(i > m_side || j > m_side) throw tetris_exception;
    	return m_grid[i][j];
    }

    bool piece::empty(uint32_t i, uint32_t j, uint32_t s) const{
    	if(s > m_side) throw tetris_exception;
    	for (uint32_t z = 0; z < m_side; ++z) {
		    for (uint32_t x = 0; x < m_side; ++x) {
		        if (m_grid[z][x]) return false;
		    }
		}
		return true;   
    }

    bool piece::full(uint32_t i, uint32_t j, uint32_t s) const{
    	if(s > m_side) throw tetris_exception;
    	for (uint32_t z = 0; z < m_side; ++z) {
		    for (uint32_t x = 0; x < m_side; ++x) {
		        if (!m_grid[z][x]) return false;
		    }
		}
		return true; 
    }

    bool piece::empty() const{
    	if(s > m_side) throw tetris_exception;
    	for (uint32_t z = 0; z < m_side; ++z) {
		    for (uint32_t x = 0; x < m_side; ++x) {
		        if (m_grid[z][x]) return false;
		    }
		}
		return true; 
    }

    bool piece::full() const{
    	if(s > m_side) throw tetris_exception;
    	for (uint32_t z = 0; z < m_side; ++z) {
		    for (uint32_t x = 0; x < m_side; ++x) {
		        if (!m_grid[z][x]) return false;
		    }
		}
		return true; 
    }

    void piece::rotate(){
    	piece rhs (this);
    	for(uint32_t i = 0; i< m_side; ++i){
    		for(uint32_t j = 0; j < m_side; ++j){
    			m_grid[j][m_side-i-1] = rhs[i][j];
    		}
    	}
    }

    void piece::cut_row(uint32_t i){
    	for(uint32_t z = i; z >= 0; --z){
    		for(uint32_t j = 0; j < m_side; ++j){
    			if(z==0){
    				m_grid[z][j] = false;
    			} else {
    				m_grid[z][j] = m_grid[z-1][j];
    			}
    		}
    	}
    }

    void piece::print_ascii_art(std::ostream& os) const{
    	
    }



    uint32_t piece::side() const{ 
    	return m_side;
    }


    int piece§::color() const {
    	return m_color;
    }



//Classe tetris


    tetris::tetris(){
    	m_score = m_width = m_height = 0;
    	m_field = nullptr;	
    }


    tetris::tetris(uint32_t w, uint32_t h, uint32_t s = 0){
    	if( w = 0 || h = 0) throw tetris_exception;
    	m_height = h;
    	m_width = w;
    	m_score = s;
    }


    tetris::tetris(tetris const& rhs){
    	m_width = rhs.m_width;
    	m_height = rhs.m_height;
    	m_score = rhs.m_score;
    	node rhs_m_field = rhs.m_field;
    	while(rhs_m_field){
    		if(!m_field){
	    		m_field->tp = new tetris_piece{rhs_m_field->tp->p, rhs_m_field->tp->x, rhs_m_field->tp->y};
	    		m_field->next = nullptr;
    		} else {
    			node tmp = m_field;
    			while(tmp-<next) tmp = tmp->next;
    			node nuovo;
    			nuovo->tp = new tetris_piece{rhs_m_field->tp->p, rhs_m_field->tp->x, rhs_m_field->tp->y};
    			nuovo->next = nullptr;
    			tmp->next = nuovo;
    		}
    		rhs_m_field = rhs_m_field->next;
    	}
    }


    tetris::tetris(tetris&& rhs){
    	m_width = rhs.m_width;
    	m_height = rhs.m_height;
    	m_score = rhs.m_score;
    	rhs.m_height = rhs.m_score = rhs.m_width = 0;
    	m_field = rhs.m_field;
    	rhs.m_field = nullptr;
    }


    tetris::~tetris(){

    }


    tetris& tetris::operator=(tetris const& rhs){

    }


    tetris& tetris::operator=(tetris&& rhs){

    }


    bool tetris::operator==(tetris const& rhs) const{

    }


    bool tetris::operator!=(tetris const& rhs) const{

    }


    void tetris::insert(piece const& p, int x){

    }


    void tetris::add(piece const& p, int x, int y){

    }


    bool tetris::containment(piece const& p, int x, int y) const{

    }


    void tetris::print_ascii_art(std::ostream& os) const{

    }